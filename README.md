# miniRT -- WIP!!

![Screenshot from 2024-04-21 21-10-07](https://github.com/alx-sch/42_pipex/assets/134595144/350670ec-54ee-4629-94ab-0dcb1dd92a9b)


<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/minirt_badge.png" alt="minirt_badge.png" />
</p>

## Ray-Object Intersection

This section explains the mathematical approach to detecting intersections between rays and various geometric objects.

### Ray Equation

A ray is represented as:

$$
P(t) = O + t \vec{D}
$$

Where:
- **$P(t)$:**  The point on the ray at distance $(t)$ from the ray's origin. It represents a location along the path defined by the ray, calculated by moving from the ray's starting point in the direction of the ray's direction vector.

- **$O$:**  The ray's origin in 3D space. This point marks the location where the ray begins its journey through space (camera).

-  **$\vec{D}$:** The normalized direction vector of the ray. A normalized vector has a magnitude (or length) of 1, ensuring that the scalar $(t)$ directly corresponds to the distance traveled along the ray.  

- **$t$:**  A scalar value indicating the distance along the ray. It scales the direction vector, determining how far along the ray the point $P(t)$ is. When the direction vector is normalized, the value of $(t)$ directly represents the magnitude of the distance from the ray’s origin.

### Plane Intersection

To find the intersection of a ray with a plane, we use the plane equation:

$$
(P - P_0) \cdot \vec{N} = 0
$$

Where:
- **$P$:** Is any point on the plane.
- **$P_0$** Is a known point on the plane 
- **$\vec{N} $:** The normal vector of the plane, which is perpendicular to the surface.

Substitute the ray equation $P(t) = O + t \vec{D}$ into the plane equation:

$$
(O + t \vec{D} - P_0) \cdot \vec{N} = 0
$$

Rearrange terms:

$$
(O - P_0) \cdot \vec{N} + t (\vec{D} \cdot \vec{N}) = 0
$$

Solve for *t*:

$$
t = \frac{(P_0 - O) \cdot \vec{N}}{\vec{D} \cdot \vec{N}}
$$

- ($t$) will be **positive** if the denominator $(\vec{D} \cdot \vec{N} )$ is positive, meaning that the ray is moving **towards** the plane. The ray will intersect the plane **in front of the camera**.
- ($t$) will be **negative** if the denominator $(\vec{D} \cdot \vec{N})$ is negative, meaning that the ray is moving **away** from the plane. The ray will intersect the **behind the camera**.
- If the denominator $(\vec{D} \cdot \vec{N} )$ is zero  (*t* is undefined or infinite), it means the ray is **parallel** to the plane and does not intersect it.

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
int	ray_intersect_plane(t_vec3 ray_origin, t_vec3 ray_dir, t_plane *plane, double *t)
{
	double	denom;		// Dot product of ray direction and plane normal
	t_vec3	difference;	// Vector from ray origin to a point on the plane

	// Compute the denominator of the intersection equation
	denom = vec3_dot(ray_dir, plane->normal);

	// Check if the ray is not parallel to the plane (denom > small threshold)
	if (fabs(denom) > 1e-6)
	{
		// Compute the vector from ray origin to a point on the plane
		difference = vec3_sub(plane->point_in_plane, ray_origin);

		// Calculate the intersection distance along the ray
		*t = vec3_dot(difference, plane->normal) / denom;

		// If the intersection distance is non-negative, the intersection is valid
		if (*t >= 0.0)
			return (1);
	}

	return (0);	// No valid intersection is found
}
```

### Quadratic Equation

Intersection calculations with geometric objects like spheres and cylinders can be solved using **quadratic equations**. A quadratic equation has the general form:

$$
ax^2 + bx + c = 0
$$

Where:
- **$x$:** The unknown variable we are solving for.
- **$a$, $b$, $c$:** The known coefficients of the equation (quadratic, linear, and constant, respectively).

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
- **$t$:** The unknown variable representing the **distance from the ray's origin** to the intersection points.
- **$a$, $b$, $c$:** Coefficients determined by the ray and object properties (e.g., direction vectors, centers, and radius).

#### Role of the Discriminant (Δ):    

The term under the root is called the discriminant ($Δ = b^2 - 4ac$), which determines the nature of the solutions:

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

The discriminant `D = b^2 - 4ac` determines the nature of the roots:
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
	double	discriminant;	 // The value of the discriminant

	// Calculate the discriminant using the formula D = b^2 - 4ac
	discriminant = (b * b) - (4.0 * a * c);

	return (discriminant);	// Return the computed discriminant
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

If ($t_1 < 0$) and ($t_2 >0$), the ray starts **within** the object and the valid intersection point is ($t_2$) (the exit point), which is **in front of the camera**. ($t_1$) is negative, corresponding to an intersection **behind the camera**, making it invalid.

### Sphere Intersection

To find where a ray intersects a sphere, we start with the general equation of the sphere:

$$
\Vert P - C \Vert^2= \left( P  - C \right) \cdot \left(P - C \right) = r^2
$$

Where:
- **$P$:** Is any point on the sphere's surface.
  
- **$C$:** The center of the sphere.
  
- **$r$:** The radius of the sphere.

Now, substitute the ray equation $P(t) = O + t \vec{D}$ into the sphere equation:

$$
\left(O + t \vec{D} - C \right) \cdot \left( O + t \vec{D} - C \right) = r^2
$$

Let $\vec{OC} = O - C$, the vector from the sphere center to the ray origin. The equation becomes:

$$
\left(\vec{OC} + t \vec{D} \right) \cdot \left( \vec{OC} + t \vec{D} \right) = r^2
$$

Expand the dot product:

$$
\left( \vec{OC} \cdot \vec{OC} \right) + 2t \left( \vec{OC} \cdot \vec{D} \right) + t^2 \left( \vec{D} \cdot \vec{D} \right) = r^2
$$

Since $\vec{D}$ is normalized ($\Vert \vec{D} \Vert=  \vec{D} \cdot \vec{D} = 1$), the equation simplifies into an quadratic equation: 

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
- **$c = (\vec{OC} \cdot \vec{OC}) - r^2$**

The following function first checks if there are any real solutions for ($t$) (discriminate >= 0).
If so, the intersection distances are calculated.

```C
/**
Function to find the intersection of a ray with a sphere.

 @param ray_origin 	The starting point of the ray in 3D space (vector).
 @param ray_dir 	The normalized direction vector of the ray.
 @param sphere 		Pointer to the sphere structure (contains center and radius).
 @param t 		Pointer to store the distance to the first intersection point (if found);
			could be the entry or exit point (if the ray is inside the sphere).

 @return 		`1` if an intersection is found (and t is set to the
			intersection distance);
			`0` if there is no intersection.

 @note 			`a = (ray_dir . ray_dir)` is 1.0 if the ray direction vector is normalized.
*/
int	ray_intersect_sphere(t_vec3 ray_origin, t_vec3 ray_dir, t_sphere *sphere, double *t)
{
	t_vec3	oc;		// Vector from ray origin to sphere center
	double	b;		// Linear coefficient in the quadratic equation
	double	c;		// Constant coefficient in the quadratic equation
	double	discriminant;	// Discriminant of the quadratic equation

	// Compute vector from ray origin to sphere center
	oc = vec3_sub(ray_origin, sphere->center);

	// Compute coefficients for the quadratic equation
	b = 2.0 * vec3_dot(oc, ray_dir);
	c = vec3_dot(oc, oc) - (sphere->radius * sphere->radius);

	// Calculate the discriminant to check for intersections
	discriminant = calculate_discriminant(1.0, b, c);

	// If the discriminant is negative, there are no real solutions (no intersection)
	if (discriminant < 0.0)
		return (0);

	// Calculate the distance to the first intersection point (smallest root)
	*t = calculate_entry_distance(1.0, b, discriminant);

	// Check if the entry point is valid (distance must be non-negative)
	if (*t >= 0.0)
		return (1);

	// Calculate the distance to the second intersection point (largest root)
	*t = calculate_exit_distance(1.0, b, discriminant);

	// Check if the exit point is valid (distance must be non-negative)
	if (*t >= 0.0)
		return (1);

	return (0);	// No valid intersection found
}
```

### Cylinder Intersection

For a cylinder with:

- An axis passing through a reference point $C=(C_x, C_y, C_z)$,
- Radius $r$,
- And a normalized orientation vector $\vec{U}$, which represents the direction of the cylinder's axis,

The general equation for a point $P=(P_x , P_y, P_z)$ on the surface of the cylinder is:

$$    
(P_x - C_x)^2 + (P_y - C_y)^2 + (P_z - C_z)^2 - \left( (P_x - C_x,  P_y - C_y,  P_z - C_z) \cdot \vec{U}\right)^2 = r^2
$$

Now define the vector from the reference point ($C$) (on the axis) to the point ($P$) (on the surface), which captures the spatial relationship between the axis and the surface point:

$$    
\vec{P} = (P_x - C_x,  P_y - C_y,  P_z - C_z)
$$

- $(P_x - C_x)^2 + (P_y - C_y)^2 + (P_z - C_z)^2 = \Vert P \Vert^2$: The square of the distance from the axis reference point $C$ to the surface point $P$.
- $(\vec{P} - \vec{U})^2$: The squared projection of $\vec{P}$ onto the axis direction $\vec{U}$, which measures the component of $\vec{P}$ along the cylinder's axis.
- Subtracting $(\vec{P} - \vec{U})^2$ removes the contribution of $\vec{P}$ along the axis, leaving only the radial distance from the axis.

The cylinder’s surface is defined by ensuring the perpendicular (radial) distance from the axis equals the radius ($r$). The following equation ensures that this condition is met:

$$
\Vert \vec{P} \Vert^2 - (\vec{P} \cdot \vec{U})^2 = r^2
$$

The parametric form of the [ray equation](https://github.com/Busedame/miniRT/blob/main/README.md#ray-equation) is:

$$
P_x(t) = O_x + tD_x
$$
$$
P_y(t) = O_y + tD_y
$$
$$
P_z(t) = O_z + tD_z
$$

Substituting this into the cylinder equation results in:

$$
\left((O_x + tD_x - C_x)^2 + (O_y + tD_y - C_y)^2 + (O_z + tD_z - C_z)^2\right) - \left((O_x - C_x + tD_x, O_y - C_y + tD_y, O_z - C_z + tD_z) \cdot \vec{U} \right)^2 = r^2
$$

which is the same as:

$$
\left(\vec{OC} +t\vec{D}\right)^2 - \left(\vec{U} \cdot \vec{OC} + t( \vec{U} \cdot \vec{D})\right)^2 = r^2
$$

Let ($\text{axis-dot-oc} = \vec{U} \cdot \vec{OC}$) and ($\text{axis-dot-ray} = \vec{U} \cdot \vec{D}$):

$$
\left(\vec{OC} +t\vec{D}\right)^2 - \left(\text{axis-dot-oc} + t(\text{axis-dot-ray})\right)^2 = r^2
$$

Expanding the two squared terms gives:

$$
\left( \vec{OC} \cdot \vec{OC} + 2t(\vec{OC} \cdot \vec{D}) + t^2(\vec{D} \cdot \vec{D})\right) - \left( (\text{axis-dot-oc})^2 + 2t(\text{axis-dot-oc} \times \text{axis-dot-ray}) + t^2(\text{axis-dot-ray})^2 \right)
$$

Expanding the squared terms of the **second part** of the equation gives:

$$
\text{axis-dot-oc}^2 + 2t(\text{axis-dot-oc} \times \text{axis-dot-ray}) + t^2(\text{axis-dot-ray})^2
$$

Grouping all this into a quadratic form ($at^2+bt+c=0$) gives the following coefficients:

- $a = (\vec{D} \cdot \vec{D}) - (\text{axis-dot-ray})^2$

- $b = 2\left( (\vec{OC} \cdot \vec{D}) - (\text{axis-dot-oc} \times \text{axis-dot-ray})\right)$

- $c = (\vec{OC} \cdot \vec{OC}) - (\text{axis-dot-oc})^2 - r^2$

The following function calculates the intersection of a ray with a cylinder using the above derivations. 

```C
/**
Function to find the intersection of a ray with a cylinder.

 @param ray_origin 	The starting point of the ray in 3D space.
 @param ray_dir 	The normalized direction vector of the ray.
 @param cylinder 	Pointer to the cylinder structure.
 @param t 		Pointer to store the distance to the first intersection point (if found);
			could be the entry or exit point (if the ray starts inside the cylinder).

 @return            	`1` if an intersection is found (and `t` is set to the intersection distance);
			`0` if there is no intersection.

 @note
This function determines intersections with an infinite cylinder surface. It does not
account for:
- The height bounds of the cylinder
- Intersection with the cylinder's end caps
*/
int	ray_intersect_cylinder(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, double *t)
{
	t_vec3	oc;	
	double	axis_dot_ray;
	double	axis_dot_oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	

	// Compute the vector from ray origin to the cylinder center
	oc = vec3_sub(ray_origin, cylinder->center);

	// Compute the dot products
	axis_dot_ray = vec3_dot(ray_dir, cyl->orientation);
	axis_dot_oc = vec3_dot(oc, cyl->orientation);

	// Compute coefficients of the quadratic equation:
	a = vec3_dot(ray_dir, ray_dir)	- (axis_dot_ray * axis_dot_ray);
	b = 2 * (vec3_dot(oc, ray_dir) - (axis_dot_oc * axis_dot_ray));
	c = vec3_dot(oc, oc) - (axis_dot_oc * axis_dot_oc) - (cylinder->radius * cylinder->radius)
	discriminant = calculate_discriminant(a, b, c);

	// If the discriminant is negative, no real solutions exist (no intersection)
	if (discriminant < 0)
		return (0);

	// Calculate the entry distance along the ray (smallest root of the quadratic)
	*t = calculate_entry_distance(cylinder->ixd.a, cylinder->ixd.b, cylinder->ixd.discriminant);

	// Check if the entry point is valid (distance must be non-negative)
	if (*t >= 0.0)
		return (1);

	// Calculate the exit distance along the ray (second root of the quadratic)
	*t = calculate_exit_distance(cylinder->ixd.a, cylinder->ixd.b, cylinder->ixd.discriminant);

	// Check if the exit point is valid (distance must be non-negative)
	if (*t >= 0.0)
		return (1);

	return (0);	// No valid intersection found
}
```
Please note that this function calculates the intersection of a ray with an infinite cylinder, not yet considering the cylinder's height and end caps. So far, it only detects intersections with the cylinder's lateral surface:

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/scene_no_height.png" alt="scene_no_height.png" width="500"/>
<p align="center">The blue and red objects are both infinite cylinders.</p>

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
   Find the component of ($\vec{V}$) along the cylinder's axis (the projection). This gives the distance along the axis from the cylinder's center to the intersection point, where ($\vec{U}$) is the normalized orientation vector representing the cylinder's axis:

$$
\text{Projection Length} = \vec{V} \cdot \vec{U}
$$

4. **Compare the projection length to the height bounds:**  
   The cylinder's height is split symmetrically around its center. If the projection length satisfies the condition below, then the intersection point is within the height bounds of the cylinder. Otherwise, it is outside the cylinder's finite height.

$$
-\frac{h}{2} \leq \text{Projection Length} \leq \frac{h}{2}
$$

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/ray_cyl_height.png" alt="ray_cyl_height.png" width="350"/>
</p>

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
static int	check_cylinder_height(t_vec3 ray_origin, t_vec3 ray_dir, double t, t_cylinder *cylinder)
{
	t_vec3	intersection_point;	// The intersection point on the cylinder
	t_vec3	center_to_point;	// Vector from cylinder center to the intersection point
	double	projection_length;	// Length of projection onto cylinder's orientation
	double	half_height;		// Half of the cylinder's total height

	 // Compute the intersection point in 3D space
	intersection_point = vec3_add(ray_origin, vec3_mult(ray_dir, t));

	// Compute the vector from the cylinder's center to the intersection point
	center_to_point = vec3_sub(intersection_point, cylinder->center);

	// Project this vector onto the cylinder's orientation axis
	projection_length = vec3_dot(center_to_point, cylinder->orientation);

	// Compute half of the cylinder's height
	half_height = cylinder->height / 2.0;

	// Check if the projection falls within the cylinder's height bounds
	if (projection_length >= -half_height && projection_length <= half_height)
		return (1);

	return (0);  // The intersection point lies outside the height bounds
}

int	ray_intersect_cylinder(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cylinder, double *t)
{
	// [...] same as in `ray_intersect_cylinder()` above

	// Check if the entry point is valid and lies within the cylinder's height bounds
	if (*t >= 0.0 && check_cylinder_height(ray_origin, ray_dir, *t, cylinder))
		return (1);

	// Calculate the exit distance along the ray
	*t = calculate_exit_distance(cylinder->ixd.a, cylinder->ixd.b, cylinder->ixd.discriminant);

	// Check if the exit point is valid and lies within the cylinder's height bounds
	if (*t >= 0.0 && check_cylinder_height(ray_origin, ray_dir, *t, cylinder))
		return (1);

	return (0);	   // No valid intersection found
}
```
<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/scene_no_caps.png" alt="scene_no_caps.png" width="500"/>
<p align="center">The blue and red cylinders are finite in height but have no caps. Looking through the blue cylinder.</p>

#### Accounting for End Caps

To account for the cylinder's end caps, the goal is to check if a ray intersects the circular regions at the top or bottom of the cylinder. These regions can be treated as planes with finite radii. The steps to determine an intersection with a cap are as follows:

1. **Represent the cap as a plane**:  
   Each cap is a circular disk on a plane perpendicular to the cylinder's axis. The plane equation for a cap is:

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
   Once ($t$) is computed, the intersection point $(\vec{P}(t))$ can be calculated using the ray equation.
   The intersection point lies within the cap if the squared length of this vector is less than or equal to the squared radius of the cap:
   
   $\Vert \vec{P}(t) - \vec{C}_{\text{cap}}  \Vert^2 \leq r^2$

```C
/**
Function to check intersection with the cylinder's cap (top or bottom).

 @param ray_origin 	The origin of the ray.
 @param ray_dir 	The normalized direction vector of the ray.
 @param cylinder 	Pointer to the cylinder structure.
 @param t 		Pointer to store the intersection distance if valid.
 @param flag_top 	Indicator for which cap to check:
                      	- `0`: bottom cap
                      	- otherwise: top cap.

 @return 		`1` if the ray intersects the cap within its radius;
			`0` otherwise.
*/
int	ray_intersect_cap(t_vec3 ray_origin, t_vec3 ray_dir, t_cylinder *cyl, double *t, int flag_top)
{
	double	denom;			// Dot product of ray direction and cap norma
	double	t_cap;			// Distance to the intersection point along the ray
	t_vec3	cap_center;		// Center of the cap being checked
	t_vec3	cap_normal;		// Normal vector of the cap
	t_vec3	to_cap_center;		// Vector from ray origin to the cap center
	t_vec3	intersection_point;	// Computed intersection point on the cap
	t_vec3	difference;		// Vector from cap center to intersection point

	// Determine cap center and normal based on the flag
	if (flag_top)
	{
		// Top cap: offset cylinder center by half its height along orientation
		cap_center = vec3_add(cyl->center, vec3_mult(cyl->orientation, cyl->height / 2.0));
		cap_normal = cyl->orientation;
	}
	else
	{
		// Bottom cap: offset cylinder center by half its height in the opposite direction
		cap_center = vec3_sub(cyl->center, vec3_mult(cyl->orientation, cyl->height / 2.0));
		cap_normal = vec3_mult(cyl->orientation, -1.0);
	}

	// Compute the denominator of the intersection equation (projection of ray direction onto cap normal)
	denom = vec3_dot(ray_dir, cap_normal);

	// If the denominator is near zero, the ray is parallel to the cap and cannot intersect
	if (fabs(denom) < 1e-6)
		return (0);

	// Calculate the distance t_cap to the intersection point on the cap plane
	to_cap_center = vec3_sub(cap_center, ray_origin);
	t_cap = vec3_dot(to_cap_center, cap_normal) / denom;

	// If the intersection is behind the ray's origin, discard it
	if (t_cap < 0.0)
		return (0);

	// Compute the actual intersection point in 3D space
	intersection_point = vec3_add(ray_origin, vec3_mult(ray_dir, t_cap));

	// Check if the intersection point lies within the cap's radius
	difference = vec3_sub(intersection_point, cap_center);
	if (vec3_dot(difference, difference) <= (cyl->radius * cyl->radius))
	{
		// Valid intersection: store the distance and return success
		*t = t_cap;
		return (1);
	}
	return (0);	// No valid intersection within the cap's radius
}
```

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/scene_complete_cyl.png" alt="scene_complete_cyl.png" width="500"/>
<p align="center">Looking at the end cap of the closed blue cylinder.</p>

#### Intersection Constants

In the ray-object intersection detection functions above, several variables are independent of the ray's direction and remain constant for a given object (e.g., ($\vec{OC}$), the quadratic coefficient ($c$), and ($\vec{OC} \cdot \vec{U}$)). While calculating these within the functions helps to understand their role and derivation here, they should be precomputed once during object initialization rather than recalculated for every single ray (or pixel).    

Precomputing these constants reduced my computation time by two-thirds for the simple scene shown in the figures above (1x plane, 2x spheres, 2x cylinders, 1440 x 900 resolution). This improvement is especially noticeable when using memory-checking tools such as Valgrind, reducing the compilation time from  ~35 sec to ~12 sec.

## Projection of 3D scene onto 2D Screen

### The Geometry of Perspective Projection

A **pinhole camera model** can be used to describe how a 3D scene is projected onto a 2D screen (viewport). The pinhole model has the following properties
- Rays originate from the camera's position (the "eye") and pass through a virtual screen plane (the viewport).
- The **field of view (FOV)** defines the angular range visible to the camera, which determines the extent of the scene captured.
- The **view frustum** is a truncated pyramid extending from the camera's position toward the viewport. The rectangular screen at the base of the frustum defines the visible scene.

<div align="center"">
<img width="600" alt="FOV_frustum" src="https://github.com/Busedame/miniRT/blob/main/.assets/FOV_frustum.png">  
</div>

<div align="center">
<img width="350" alt="Viewpoint_FOV" src="https://github.com/Busedame/miniRT/blob/main/.assets/Viewport_Field_of_View.png">  
</div>

### Ray Direction Calculation

The **Field of View (FOV)** represents how much of the 3D scene is visible to the camera. Depending on the orientation of the camera, the FOV could be horizontal or vertical:

- The vertical FOV ($\text{FOV}_v$) is the angle between the top and bottom edges of the view frustum.
- The horizontal FOV ($\text{FOV}_h$) is the angle between the left and right edges of the view frustum.

Vertical FOV is often the most common in graphics programming, but horizontal FOV can also be defined depending on the viewport dimensions.

We employ trigonometric functions, specifically the tangent function, to calculate how this FOV scales the projection from 3D space onto 2D screen space.

### Geometric Relationship Using Tangent

Imagine a right triangle formed by:
1. The **camera's position** (the "eye") as the vertex.
2. **A point on the top edge** of the screen as one endpoint.
3. **The center of the screen** as the other endpoint.

The angle between the screen's center and the top edge of the frustum corresponds to $\frac{\text{FOV}_v}{2}$.   

Using $\tan(\text{angle}) = \frac{\text{opposite}}{\text{adjacent}}$, we can represent this relationship mathematically:

$$
\tan\left(\frac{\text{FOV}_v}{2}\right) = \frac{\text{Half the Screen Height}}{\text{Distance to Screen}}
$$

<p align="center">
	<img width="350" alt="tan_FOV" src="https://github.com/Busedame/miniRT/blob/main/.assets/tan_FOV.png">  
<p align="center"> </p>


The tangent function defines the "scaling factor" that maps world-space distances to screen-space distances, ensuring that closer objects appear larger and distant objects appear smaller.   
Changing the FOV changes $\tan\left(\frac{\text{FOV}_v}{2}\right)$, which directly affects the scaling. A wider FOV results in a smaller tangent value, making objects appear farther away (and vice versa).

In C, trigonometric functions expect their input angles to be in radians, not degrees. Therefore, the FOV angle is converted using the formula $Radians = Degrees \times \frac{\pi}{180}$ in the function below

### Ray Direction Calculation

The direction of a ray corresponding to a pixel on the viewport is calculated using normalized device coordinates. These calculations map the 2D screen space into 3D world-space rays.

**Steps to Calculate Ray Direction:**

1. **FOV Scaling Factor:**    
   The tangent of half the vertical FOV defines how much the view scales with distance.
   
$$
\text{scale} = \tan\left(\frac{\text{FOV}_v}{2}\right) \text{(converted into radians)}
$$

2. **Normalization of Pixel Coordinates:**    
   When projecting a 3D scene from world space to a 2D viewport, we need to map the 2D pixel coordinates of the screen to a common mathematical range known as **normalized device 
   coordinates (NDC)**. These coordinates range from -1 to 1 in both horizontal and vertical directions. This mapping allows the rendering process to operate independently of the actual 
   screen resolution, making the projection consistent regardless of the screen size.

   We map these screen pixel positions (`x`, `y`) to a range of [-1, 1] so they are consistent and independent of the screen's resolution:
   - **Horizontal NDC Mapping:** `norm_x = (2.0 * (x + 0.5) / WINDOW_W) - 1.0` ensures that the leftmost pixel maps to `-1` and the rightmost pixel maps to `1`. The term `(x + 0.5)` ensures to center the mapping is at the pixel's center rather than at the pixel's edge (so the values for `norm_x` are close to but not exactly `-1` and `1`, differing by a small fraction).
   - **Vertical NDC Mapping:** `norm_y = (1.0 - (2.0 * (y + 0.5) / WINDOW_H))`, with the topmost pixel mapping to `1` and bottommost one mapping to `-1`. Similar to the horizontal case, `(y + 0.5)` ensures the mapping is centered on the pixel.

3. **Aspect Ratio Adjustment:**    
  The aspect ratio ensures that the spatial proportions of objects remain accurate across displays with different width-to-height ratios. Without this adjustment, objects might appear 
  stretched or squished, especially on non-square screens. 

   The aspect ratio is defined as `aspect_ratio = WINDOW_W / WINDOW_H`.
  
    In this implementation, the vertical FOV is used as the starting point for perspective projection calculations. This means that the vertical dimensions are already 
  correctly scaled according to the screen height and FOV.   
  
    Thus, the aspect ratio is applied to the horizontal NDC calculation only: `norm_x = ((2.0 * (x + 0.5) / WINDOW_W) - 1.0) * aspect_ratio`
  
4. **Putting It All Together:**  
   - Map pixel indices (`x`, `y`) to the normalized device coordinate range [-1, 1].
   - Adjust horizontal values by the aspect ratio to maintain spatial proportions for non-square displays.
   - Scale both normalized x and y values by the field of view's scaling factor derived from the tangent of half the vertical FOV.
   - Normalize these values to ensure they map correctly to 3D space for ray calculations.

```C
/**
Compute the direction vector of a ray passing through a given pixel in the camera's view.

 @param x	The horizontal pixel coordinate on the screen.
 @param y	The vertical pixel coordinate on the screen.
 @param cam	The camera object containing the FOV in degrees.

 @return	The normalized direction vector of the ray in camera space.

 @note
The z-component of the ray direction is set to 1.0 as a convention.
This places the projection plane (screen) at z = 1.0 in camera space, which simplifies
the perspective projection math. The vector is then normalized to ensure it has a unit length,
making it independent of this initial choice for z.
*/
t_vec3	compute_ray_direction(int x, int y, t_cam cam)
{
	double	scale;		// Scaling factor from the vertical FOV
	double	aspect_ratio;	// Ratio of screen width to height
	double	norm_x;		// Normalized x-coordinate in NDC
	double	norm_y;		// Normalized y-coordinate in NDC
	t_vec3	ray_dir;	// Ray direction vector

	scale = tan((cam.fov / 2) * M_PI / 180.0);

	aspect_ratio = (double)WINDOW_W / (double)WINDOW_H;

	// Map pixel coordinates to normalized device coordinates (NDC)
	norm_x = ((2.0 * (x + 0.5) / WINDOW_W) - 1.0) * aspect_ratio * scale;
	norm_y = (1.0 - (2.0 * (y + 0.5) / WINDOW_H)) * scale;

	// Construct the direction vector in camera space
	ray_dir.x = norm_x;
	ray_dir.y = norm_y;
	ray_dir.z = 1.0;	// Pointing forward in camera space.

        // Normalize the direction vector to ensure it has a unit length
	return (vec3_norm(ray_dir));
}
```

### Handling Camera Orientation

XXX
