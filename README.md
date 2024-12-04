# miniRT -- WIP!!

![Screenshot from 2024-04-21 21-10-07](https://github.com/alx-sch/42_pipex/assets/134595144/350670ec-54ee-4629-94ab-0dcb1dd92a9b)


<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/minirt_badge.png" alt="minirt_badge.png" />
</p>

## Projection of 3D scene onto 2D Screen

<div style="display: block;">
<img width="600" alt="Viewpoint_FOV" src="https://github.com/Busedame/miniRT/blob/main/.assets/Viewport_Field_of_View.png">  
</div>

<div style="display: block;">
<img width="830" alt="FOV_frustum" src="https://github.com/Busedame/miniRT/blob/main/.assets/FOV_frustum.png">  
</div>

- The camera has a frustum that defines what it can see (a 3D pyramid-like shape).
- The near plane is the closest part of the frustum to the camera, and it's like a window through which the camera views the 3D world (until the far plane).
- The viewport is the 2D version of that window (the near plane) where the 3D world gets projected and displayed on the screen.

## Ray-Object Intersection

This section explains the mathematical approach to detecting intersections between rays and various geometric objects.

### Ray Equation

A ray is represented as:

$$
\vec{P}(t) = \vec{O} + t \vec{D}
$$

Where:
- **$\vec{P}(t)$:**  
    The point on the ray at distance \(t\) from the ray's origin.  
    It represents a location along the path defined by the ray, calculated by moving from the ray's starting point in the direction of the ray's direction vector.

- **$\vec{O}$:**  
    The ray's origin, represented as a 3D vector.  
    This point marks the location where the ray begins its journey through space (camera).

-  **$\vec{D}$:**  
    The normalized direction vector of the ray.  
    A normalized vector has a magnitude (or length) of 1, ensuring that the scalar \(t\) directly corresponds to the distance traveled along the ray.  

- **$t$:**  
    A scalar value indicating the distance along the ray.  
    It scales the direction vector, determining how far along the ray the point \( P(t) \) is. When the direction vector is normalized, the value of \(t\) directly represents the magnitude of the distance from the ray’s origin.

### Plane Intersection

To find the intersection of a ray with a plane, we use the plane equation:

$$
(\vec{P} - \vec{P_0}) \cdot n = 0
$$

Where:
- **$\vec{P}$:**   
    Is any point on the plane.
- **$\vec{P_0}$**  
    Is a known point on the plane 
- **$n$:**  
    The normal vector of the plane, which is perpendicular to the surface.

Substitute the ray equation ' $P(t) = \vec{O} + t \vec{D}$ ' into the plane equation:

$$
(\vec{O} + t \vec{D} - \vec{P_0}) \cdot n = 0
$$

Rearrange terms:

$$
(\vec{O} - \vec{P_0}) \cdot n + t (\vec{D} \cdot n) = 0
$$

Solve for *t*:

$$
t = \frac{(P_0 - \vec{O}) \cdot n}{\vec{D} \cdot n}
$$

- *t* will be **positive** if the denominator ' $\vec{D} \cdot n$ ' is positive, meaning that the ray is moving **towards** the plane. The ray will intersect the plane **in front of the camera**.
- *t* will be **negative** if the denominator ' $\vec{D} \cdot n$ ' is negative, meaning that the ray is moving **away** from the plane. The ray will intersect the **behind the camera**.
- If the denominator ' $\vec{D} \cdot n$ ' is zero  (*t* is undefined or infinite), it means the ray is **parallel** to the plane and does not intersect it.

In the function, we first check if the ray is not parallel to the plane (*t* exists or is defined). If the ray is not parallel, we then check if the intersection happens in front of the camera (*t* is positive). The function returns successfully only if the intersection occurs in front of the camera.

```C
/**
Function to find the intersection of a ray with a plane.

 @param ray_origin	The starting point of the ray (3D vector).
 @param ray_dir 	The normalized direction vector of the ray.
 @param plane 		Pointer to the plane structure.
 @param t 		A pointer to store the distance to the intersection point (if found).

 @return 		`1` if an intersection is found in the FOV (and `t` is set to the
			intersection distance);
			`0` if there is no intersection within the FOV (ray is parallel to the
			plane or intersection behind the camera).

 @note
Due to floating-point precision limitations, directly comparing a dot product to zero can be
unreliable. A small threshold (1e-6) is used to determine if the ray is parallel to the plane.
Values below this threshold are considered too close to zero, indicating parallelism or
preventing division by very small numbers, which could lead to inaccuracies.
*/
int	ray_intersect_plane(t_vec3 ray_origin, t_vec3 ray_dir, t_plane *plane,
		double *t)
{
	double	denom;
	t_vec3	difference;

	denom = vec3_dot(ray_dir, plane->normal);
	if (fabs(denom) > 1e-6)
	{
		difference = vec3_sub(plane->point_in_plane, ray_origin);
		*t = vec3_dot(difference, plane->normal) / denom;
		if (*t >= 0.0)
			return (1);
	}
	return (0);
}
```

### Quadratic Equation

Intersection calculations with geometric objects like spheres and cylinders can be solved using **quadratic equations**. A quadratic equation has the general form:

$$
ax^2 + bx + c = 0
$$

Where:
- **$x$:**    
  The unknown variable we are solving for.
- **$a$, $b$, $c$:**    
  The known coefficients of the equation (quadratic, linear, and constant, respectively).

The general solution to a quadratic equation is given by the **quadratic formula**:

$$
x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a}
$$

For a detailed derivation of the quadratic formula, please refer to [ChiliMath Quadratic Formula Derivation](https://www.chilimath.com/lessons/intermediate-algebra/derive-quadratic-formula/).

### Quadratic Intersections in Ray Tracing

In context of the miniRT project, calculating intersections with objects like **spheres** or **cylinders** involves solving a quadratic equation of the form

$$
at^2 + bt + c = 0
$$

which solves into

$$
t = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a}
$$

Where:
- **$t$:**    
  The unknown variable representing the **distance from the ray's origin** to the intersection points.
- **$a$, $b$, $c$:**    
  Coefficients determined by the ray and object properties (e.g., direction vectors, centers, and radius).

#### Role of the Discriminant (Δ):    

The term under the root is called the discriminant ( $Δ = b^2 - 4ac$ ), which determines the nature of the solutions:

1. **Δ > 0**: Two distinct real solutions ($t_1$ and $t_2$):
   - The ray intersects the object at **two points**.
   - These points correspond to **entering** and **exiting** the object.

2. **Δ = 0**: One real solution ($t_1 = t_2$):
   - The ray is **tangent** to the object, touching it at a **single point**.

3. **Δ < 0**: No real solutions:
   - The ray does **not intersect** the object.

```C
/**
Calculates the discriminant of a quadratic equation `ax^2 + bx + c = 0`, which solves into
`x = (-b ± sqrt(b^2 - 4ac)) / 2a`.

The discriminant `D = b^2 - 4ac` tells us:
- if `D > 0`, there are two real roots (the ray intersects the object at two
  points).
- if `D = 0`, there is one real root (the ray is tangent to the object, touching
  it at one point).
- if `D < 0`, there are no real roots (the ray does not intersect the object).

 @param a 	The coefficient of the quadratic term in quadratic equation.
 @param b 	The coefficient of the linear term in quadratic equation.
 @param c 	The constant term in quadratic equation.

 @return 	The discriminant of the quadratic equation.
*/
double	calculate_discriminant(double a, double b, double c)
{
	double	discriminant;

	discriminant = (b * b) - (4.0 * a * c);
	return (discriminant);
}
```

#### Special case: Camera Inside the Object

The intersection distances $t_1$ (entry) and $t_2$ (exit) are calculates as follows:   

$$
t_1 = \frac{-b - \sqrt{b^2 - 4ac}}{2a}
$$
$$
t_2 = \frac{-b + \sqrt{b^2 - 4ac}}{2a}
$$

If $t_1 < 0$ and $t_2 >0$, the ray starts **within** the object and the valid intersection point is $t_2$ (the exit point), which is **in front of the camera**. $t_1$ is negative, corresponding to an intersection **behind the camera**, making it invalid.

### Sphere Intersection

To find where a ray intersects a sphere, we start with the general equation of the sphere:

$$
\|\| \vec{P} - \vec{C} \|\|^2= \left( \vec{P}  - \vec{C} \right) \cdot \left(\vec{P} - \vec{C} \right) = r^2
$$

Where:
- **$\vec{P}$:**   
    Is any point on the sphere's surface (3D vector).
  
- **$\vec{C}$:**  
    The center of the sphere (3D vector).
  
- **$r$:**  
    The radius of the sphere.

Now, substitute the ray equation ' $\vec{P}(t) = \vec{O} + t \vec{D}$ ' into the sphere equation:

$$
\left(\vec{O} + t \vec{D} - \vec{C} \right) \cdot \left( \vec{O} + t \vec{D} - \vec{C} \right) = r^2
$$

Let $\vec{OC} = \vec{O} - \vec{C}$, the vector from the sphere center to the ray origin. The equation becomes:

$$
\left(\vec{OC} + t \vec{D} \right) \cdot \left( \vec{OC} + t \vec{D} \right) = r^2
$$

Expand the dot product:

$$
\left( \vec{OC} \cdot \vec{OC} \right) + 2t \left( \vec{OC} \cdot \vec{D} \right) + t^2 \left( \vec{D} \cdot \vec{D} \right) = r^2
$$

Since $\vec{D}$ is normalized ($\|\|\vec{D}\|\| =  \vec{D} \cdot \vec{D} = 1$), the equation simplifies into an quadratic equation: 

$$
t^2 +  2t \left( \vec{OC} \cdot \vec{D} \right) + \left( \vec{OC} \cdot \vec{OC} \right) - r^2 = 0
$$

As explained [above](https://github.com/Busedame/miniRT/blob/main/README.md#quadratic-intersections-in-ray-tracing), this solves into:

$$
t = \frac{-b \pm \sqrt{b^2 - 4c}}{2}
$$

Where the coefficients are:

- **$a = 1$**
- **$b = 2(\vec{OC} \cdot \vec{D}$)**
- **$c = \left( \vec{OC} \cdot \vec{OC} \right) - r^2$**

The following function first checks if there are any real solutions for $t$ (discriminate >= 0).
If so, the intersection distances are calculated.
```C
/**
Function to find the intersection of a ray with a sphere.

 @param ray_origin 	The starting point of the ray (3D vector).
 @param ray_dir 	The direction vector of the ray (assumed to be normalized).
 @param sphere 		Pointer to the sphere structure (contains center and radius).
 @param t 		Pointer to store the distance to the first intersection point (if found);
			could be the entry or exit point (if the ray is inside the sphere).

 @return 		`1` if an intersection is found (and t is set to the
			intersection distance);
			`0` if there is no intersection.

 @note 			`a = (ray_dir . ray_dir)` is 1.0 if the ray direction vector is normalized.
*/
int	ray_intersect_sphere(t_vec3 ray_origin, t_vec3 ray_dir, t_sphere *sphere,
		double	*t)
{
	t_vec3	oc;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(ray_origin, sphere->center);
	b = 2.0 * vec3_dot(oc, ray_dir);
	c = vec3_dot(oc, oc) - (sphere->radius * sphere->radius);
	discriminant = calculate_discriminant(1.0, b, c);
	if (discriminant < 0.0)
		return (0);
	*t = calculate_entry_distance(1.0, b, discriminant);
	if (*t >= 0.0)
		return (1);
	*t = calculate_exit_distance(1.0, b, discriminant);
	if (*t >= 0.0)
		return (1);
	return (0);
}
```
### Cylinder Intersection

For a cylinder with a given center at $(C_x, C_y, C_z)$, radius $r$, and a normalized orientation vector $\vec{U}$ (which represents its axis), the general equation is:

$$    
(x - C_x)^2 + (y - C_y)^2 + (z - C_z)^2 - ((x, y, z) \cdot \vec{U})^2 = r^2
$$

Where $(x,y,z)$ represents any point on the cylinder’s surface, and $(x,y,z) \cdot \vec{U}$ is the dot product that measures how much of the position vector (from the center of the cylinder) lies along the cylinder's axis.

This equation is equivalent to:

$$
\|\| \vec{P} |\|^2 - (\vec{P} \cdot \vec{U})^2 = r^2
$$

Here
- $\|\| \vec{P} |\|^2 = (P_x - C_x)^2 + (P_y - C_y)^2 + (P_z - C_z)^2$ is the squared distance of $\vec{P}$ from the center.
- $(\vec{P} \cdot \vec{U})^2$ removes the squared distance contribution along the axis.

This leaves only the perpendicular distance from the axis, ensuring that any point on the cylinder's surface satisfies the condition of being at a fixed radial distance 
$r$ from the axis, independent of the cylinder's center.

The parametric form of the [ray equation](https://github.com/Busedame/miniRT/blob/main/README.md#ray-equation) is:

$$
x(t) = O_x + tD_x
$$
$$
y(t) = O_y + tD_y
$$
$$
z(t) = O_z + tD_z
$$

Substituting this into the cylinder equation results in:

$$
((O_x + tD_x - C_x)^2 + (O_y + tD_y - C_y)^2 + (O_z + tD_z - C_z)^2) - ((O_x + tD_x, O_y + tD_y, O_z + tD_z) \cdot U)^2 = r^2
$$

Now for the projection, we compute the dot products of the ray direction and the vector from the ray’s origin to the cylinder center with the cylinder’s orientation vector:

$$    
\text{axis-dot-ray} = \vec{D} \cdot \vec{U}
$$

This gives how much of the ray’s direction aligns with the cylinder’s axis. It’s important for determining the ray's motion along the cylinder’s axis.

$$
\text{axis-dot-oc} = \vec{OC} \cdot \vec{U}
$$

This gives how much of the vector from the ray’s origin to the cylinder’s center aligns with the cylinder’s axis. It helps determine the starting position relative to the axis of the cylinder.

Using these dot products as substitutions in the ray-cylinder-intersection equation results in:

$$
((O_x + tD_x - C_x)^2 + (O_y + tD_y - C_y)^2 + (O_z + tD_z - C_z)^2) - (\text{axis-dot-oc} + t(\text{axis-dot-ray}))^2 = r^2
$$

Expanding each squared term of the **first part** of the equation gives

$$
(O_x + tD_x - C_x)^2 = (O_x - C_x)^2 + 2t(O_x - C_x)D_x + t^2D^2_x 
$$
$$
(O_y + tD_y - C_y)^2 = (O_y - C_y)^2 + 2t(O_y - C_y)D_y + t^2D^2_y 
$$
$$
(O_z + tD_z - C_z)^2 = (O_z - C_z)^2 + 2t(O_z - C_z)D_z + t^2D^2_z 
$$

Expanding the squared terms of the **second part** of the equation gives:

$$
\text{axis-dot-oc}^2 + 2t(\text{axis-dot-oc} \times \text{axis-dot-ray}) + t^2(\text{axis-dot-ray})^2
$$

Grouping all this into a quadratic form ($at^2+bt+c=0$) gives the following coefficients:

- $a = D^2_x + D^2_y + D^2_z - \text{axis-dot-ray}^2 = \vec{D} \cdot \vec{D} - \text{axis-dot-ray}^2$

- $b = 2( (O_x - C_x)D_x + (O_y - C_y)D_y + (O_z - C_z)D_z - \text{axis-dot-oc} \times \text{axis-dot-ray} ) = 2( \vec{OC} \cdot \vec{D} - \text{axis-dot-oc} \times \text{axis-dot-ray} )$

- $c = (\vec{O} - \vec{C})^2 - \text{axis-dot-oc}^2 - r^2  = \vec{OC} \cdot \vec{OC} - \text{axis-dot-oc}^2 - r^2$

The following function calculates the intersection of a ray with a cylinder using the above derivations. 

```C
/**
Function to calculate the coefficients of the quadratic equation and other variables
for the intersection of a ray with a cylinder.

 @param cyl 		Pointer to the cylinder structure.
 @param ray_dir 	The normalized direction vector of the ray.
 @param oc 		The vector from the ray origin to the cylinder center.

 @return		None. The function modifies the cylinder's `ixd` structure
			to store the calculated coefficients and the discriminante.
*/
static void	compute_cylinder_intersection_vars(t_cylinder *cyl, t_vec3 ray_dir, t_vec3 oc)
{
	double	axis_dot_ray;
	double	axis_dot_oc;

	axis_dot_ray = vec3_dot(ray_dir, cyl->orientation);
	axis_dot_oc = vec3_dot(oc, cyl->orientation);
	cyl->ixd.a = vec3_dot(ray_dir, ray_dir)	- pow(axis_dot_ray, 2);	// ixd: intersection data
	cyl->ixd.b = 2 * (vec3_dot(oc, ray_dir) - axis_dot_oc * axis_dot_ray);
	cyl->ixd.c = vec3_dot(oc, oc) - pow(axis_dot_oc, 2) - pow(cyl->radius, 2);
	cyl->ixd.discriminant = calculate_discriminant(cyl->ixd.a, cyl->ixd.b, cyl->ixd.c);
}

/**
Function to find the intersection of a ray with a cylinder.

 @param ray_origin 	The starting point of the ray.
 @param ray_dir 	The ray's direction vector (assumed to be normalized).
 @param cylinder 	Pointer to the cylinder structure.
 @param t 		Pointer to store the distance to the first intersection point (if found);
			could be the entry or exit point (if the ray starts inside the cylinder).

 @return            	`1` if an intersection is found (and `t` is set to the
			intersection distance);
			`0` if there is no intersection.

 @note 			This function does not take into account:
			- The height bounds of the cylinder
			- Intersection with the cylinder's end caps
*/
int	ray_intersect_cylinder(t_vec3 ray_origin, t_vec3 ray_dir,
		t_cylinder *cylinder, double *t)
{
	t_vec3	oc;

	oc = vec3_sub(ray_origin, cylinder->center);
	compute_cylinder_intersection_vars(cylinder, ray_dir, oc);
	if (cylinder->ixd.discriminant < 0)
		return (0);
	*t = calculate_entry_distance(cylinder->ixd.a, cylinder->ixd.b, cylinder->ixd.discriminant);
	if (*t >= 0.0)
		return (1);
	*t = calculate_exit_distance(cylinder->ixd.a, cylinder->ixd.b, cylinder->ixd.discriminant);
	if (*t >= 0.0)
		return (1);
	return (0);
}
```
Please note that this function calculates the intersection of a ray with an infinite cylinder, not yet considering the cylinder's height and end caps. So far, it only detects intersections with the cylinder's lateral surface (the blue and red objects in the rendering below are both infinite cylinders):

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/scene_no_height.png" alt="scene_no_height.png" width="500"/>
</p>

#### Handling the Cylinder's Height

To account for the height boundaries of the cylinder, follow these steps:

1. **Find the intersection point:**    
   Use the ray equation with the calculated intersection distance $t$:
   
$$
\vec{P}(t) = \vec{O} + t \vec{D}
$$

2. **Compute a vector to the cylinder's center:**

$$
\vec{V} = \vec{P} - \vec{C}
$$

3. **Project this vector onto the cylinder's axis:**       
   Find the component of $\vec{V}$ along the cylinder's axis (the projection). This gives the distance along the axis from the cylinder's center to the intersection point, where $\vec{U}$ is the normalized orientation vector representing the cylinder's axis:

$$
\text{Projection Length} = \vec{V} \cdot \vec{U}
$$

4. **Compare the projection length to the height bounds:**  
   The cylinder's height is split symmetrically around its center. If the projection length satisfies the condition below, then the intersection point is within the height bounds of the cylinder. Otherwise, it is outside the cylinder's finite height.

$$
-\frac{h}{2} \leq \text{Projection Length} \leq \frac{h}{2}
$$

```C
/**
Function to check whether a given intersection point on an infinite cylinder lies
within the cylinder's finite height bounds.

 @param ray_origin 	The origin of the ray in 3D space.
 @param ray_dir 	The normalized direction vector of the ray.
 @param t 		The distance along the ray to the intersection point.
 @param cylinder 	Pointer to the cylinder structure.

 @return 		`1` if the intersection point lies within the cylinder's
			height bounds;
			`0` otherwise.
*/
static int	check_cylinder_height(t_vec3 ray_origin, t_vec3 ray_dir, double t,
		t_cylinder *cylinder)
{
	t_vec3	intersection_point;
	t_vec3	center_to_point;
	double	projection_length;
	double	half_height;

	intersection_point = vec3_add(ray_origin, vec3_mult(ray_dir, t));
	center_to_point = vec3_sub(intersection_point, cylinder->center);
	projection_length = vec3_dot(center_to_point, cylinder->orientation);
	half_height = cylinder->height / 2.0;
	if (projection_length >= -half_height && projection_length <= half_height)
		return (1);
	return (0);
}

int	ray_intersect_cylinder(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, double *t)
{
	t_vec3	oc;

	oc = vec3_sub(ray_origin, cylinder->center);
	compute_cylinder_intersection_vars(cylinder, ray_dir, oc);
	if (cylinder->ixd.discriminant < 0)
		return (0);
	*t = calculate_entry_distance(cylinder->ixd.a, cylinder->ixd.b, cylinder->ixd.discriminant);
	if (*t >= 0.0 && check_cylinder_height(ray_origin, ray_dir, *t, cylinder))
		return (1);
	*t = calculate_exit_distance(cylinder->ixd.a, cylinder->ixd.b, cylinder->ixd.discriminant);
	if (*t >= 0.0 && check_cylinder_height(ray_origin, ray_dir, *t, cylinder))
		return (1);
	return (0);
}
```

The blue and red cylinders in the following rendering are finite in height but have no caps:

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/scene_no_caps.png" alt="scene_no_caps.png" width="500"/>
</p>

#### Accounting for End Caps

To account for the cylinder's end caps, the goal is to check if a ray intersects the circular regions at the top or bottom of the cylinder. These regions can be treated as planes with finite radii. The steps to determine an intersection with a cap are as follows:

1. **Represent the cap as a plane**:  
   Each cap is a circular disk lying on a plane perpendicular to the cylinder's axis. The plane equation for a cap is:

   $(\vec{P} - \vec{C}_{\text{cap}}) \cdot \vec{U} = 0$

   Here:  
   - $\(\vec{C}_{\text{cap}}\)$ is the center of the cap (top or bottom).  
   - $\(\vec{U}\)$ is the normalized orientation vector of the cylinder's axis.  
   - $\(\vec{P}\)$ is a point on the plane (we will test for the ray-plane intersection).

2. **Find the ray-plane intersection:**     
   Substitute the ray equation ($\vec{P}(t) = \vec{O} + t \vec{D}$) into the plane equation:

   $((\vec{O} + t \vec{D}) - \vec{C}_{\text{cap}}) \cdot \vec{U} = 0$

   Where:
   - $\(\vec{O}\)$ is the ray origin.  
   - $\(\vec{D}\)$ is the normalized direction vector of the ray
   - $\(t\)$ is the distance from $\(\vec{O}\)$ to the intersection point.

   Simplify:
   
   $(\vec{O} - \vec{C}_{\text{cap}}) \cdot \vec{U} + t(\vec{D} \cdot \vec{U}) = 0$

   Solve for $t$:
   
   $t = \frac{(\vec{C}_{\text{cap}} - \vec{O}) \cdot \vec{U}}{\vec{D} \cdot \vec{U}}$

4. **Check the intersection point against the cap's radius:**    
   Once $t$ is computed, the intersection point $\vec{P}(t)$ can be calculated using the ray equation.
   The intersection point lies within the cap if the squared length of this vector is less than or equal to the squared radius of the cap:
   
   $\|\| \vec{P}(t) - \vec{C}_{\text{cap}}  \|\|^2 \leq r^2$

```C
/**
Function to check intersection with the cylinder's cap (top or bottom).

 @param ray_origin 	The origin of the ray.
 @param ray_dir 	The normalized direction vector of the ray.
 @param cylinder 	Pointer to the cylinder structure.
 @param t 		Pointer to store the intersection distance if valid.
 @param flag_top 	Flag to indicate whether the top or bottom cap is being checked
			(`0`: bottom; otherwise: top).

 @return 		`1` if the ray intersects the cap within its radius;
			`0` otherwise.
*/
int	ray_intersect_cap(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cyl, double *t, int flag_top)
{
	double	denom;
	double	t_cap;
	t_vec3	cap_center;
	t_vec3	cap_normal;
	t_vec3	to_cap;
	t_vec3	intersection_point;
	t_vec3	difference;

	if (flag_top)
	{
		cap_center = vec3_add(cyl->center, vec3_mult(cyl->orientation, cyl->height / 2.0));
		cap_normal = cyl->orientation;
	}
	else
	{
		cap_center = vec3_sub(cyl->center, vec3_mult(cyl->orientation, cyl->height / 2.0));
		cap_normal = vec3_mult(cyl->orientation, -1.0);
	}
	denom = vec3_dot(ray_dir, cap_normal);
	if (fabs(denom) < 1e-6)
		return (0);
	to_cap = vec3_sub(cap_center, ray_origin);
	t_cap = vec3_dot(to_cap, cap_normal) / denom;
	if (t_cap < 0.0)
		return (0);
	intersection_point = vec3_add(ray_origin, vec3_mult(ray_dir, t_cap));
	difference = vec3_sub(intersection_point, cap_center);
	if (vec3_dot(difference, difference) <= (cyl->radius * cyl->radius))
	{
		*t = t_cap;
		return (1);
	}
	return (0);
}
```

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/scene_complete_cyl.png" alt="scene_complete_cyl.png" width="500"/>
</p>

#### Intersection Constants

In the ray-object intersection detection functions above, several variables are independent of the ray's direction and remain constant for a given object (e.g., $\vec{OC}$, the quadratic coefficient $c$, and $\vec{OC} \cdot \vec{U}$). While calculating these within the functions helps to understand their role and derivation here, they should be precomputed during object initialization rather than recalculated for every single ray (or pixel).    

Precomputing these constants reduced my computation time by two-thirds for a simple scene (1x plane, 2x spheres, 2x cylinders, 1440 x 900 resolution). This improvement is especially noticeable when using memory-checking tools such as Valgrind, reducing the compilation time from  ~35 sec to ~12 sec.
