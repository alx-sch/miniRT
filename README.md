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
 @param t 		A pointer to store the distance to the intersection point
			(if found).

 @return 		`1` if an intersection is found in the FOV (and `t` is set
			to the intersection distance);
			`0` if there is no intersection within the FOV (ray is
			parallel to the plane or intersection is behind the camera).

 @note
Due to floating-point precision limitations, directly comparing a dot product
to zero can be unreliable. A small threshold (1e-6) is used to determine if the
ray is parallel to the plane. Values below this threshold are considered too
close to zero, indicating parallelism or preventing division by very small
numbers, which could lead to inaccuracies.
*/
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

In context of the miniRT project, calculating intersections with objects like **spheres** or **cylinders** involve solving a quadratic equation of the form

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

The term under the root is called the discrimant ( $Δ = b^2 - 4ac$ ), which determines the nature of the solutions:

1. **Δ > 0**: Two distinct real solutions ($t_1$ and $t_2$):
   - The ray intersects the object at **two points**.
   - These points correspond to **entering** and **exiting** the object.

2. **Δ = 0**: One real solution ($t_1 = t_2$):
   - The ray is **tangent** to the object, touching it at a **single point**.

3. **Δ < 0**: No real solutions:
   - The ray does **not intersect** the object.

```C
/**
Calculates the discriminant of a quadratic equation `ax^2 + bx + c = 0`, which
solves into `x = (-b ± sqrt(b^2 - 4ac)) / 2a`.

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
 @param t 		Pointer to store the distance to the first intersection
			point (if found); could be the enter or exit point (if the
			ray is inside the sphere).

 @return 		`1` if an intersection is found (and t is set to the
			intersection distance);
			`0` if there is no intersection.

 @note 			`a = (ray_dir . ray_dir)` is 1.0 if the ray direction
			vector is normalized.
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
	if (discriminant >= 0.0)
	{
		*t = calculate_entry_distance(1.0, b, discriminant);
		if (*t >= 0.0)
			return (1);
		*t = calculate_exit_distance(1.0, b, discriminant);
		if (*t >= 0.0)
			return (1);
	}
	return (0);
}
```
### Cylinder Intersection (Side)

For a cylinder in 3D space, the general equation with a given center at $(C_x, C_y, C_z)$, radius $r$, and a normalized orientation vector $\vec{U}$, the equation for a cylinder is:

$$    
((x - C_x)^2 + (z - C_y)^2 + (z - C_z)^2) - ((x, y, z) \cdot \vec{U})^2 = r^2
$$

Where $(x,y,z)$ represents any point on the cylinder’s surface, and $(x,y,z) \cdot \vec{U}$ is the dot product that measures how much of the position vector (from the center of the cylinder) lies along the cylinder's axis.

- If the position vector $(x,y,z)$ is aligned with the axis vector $\vec{U}$, the dot product is large, indicating the point is far along the axis.
- If the position vector is perpendicular to the axis, the dot product is zero, meaning the point lies in the plane perpendicular to the axis (same cross-section as the center).
- If the position vector is in the opposite direction of the axis, the dot product is negative, indicating the point is on the opposite side of the axis.


The cylinder is described as an infinitely long cylinder aligned along the **y-axis**, with its circular cross-section in the $xz$-plane. The general equation for such a cylinder, given its center at $(C_x, C_z)$ in the $xz$-plane and radius $r$, is:

$$    
(x - C_x)^2 + (z - C_z)^2 = r^2
$$    

For simplicity, let'stranslate the cylinder’s center to the origin in the $xz$-plane. After translation, the cylinder's equation simplifies to:

$$    
x^2 + z^2 = r^2
$$

This makes it easier to solve the intersection with the ray without having to account for the center offsets in the $x$- and $z$-directions.

The $x$- and $z$-coordinates of the ray at a distance $t$ from it's origin are:

$$    
x(t) = O_x + tD_x
$$
$$
z(t) = O_z + tD_z
$$

$y(t)$ won't affect the cylinder intersection and is thus not regarded here.

Now, substitute the ray's parametric equations for $x(t)$ and $z(t)$ into the simplified cylinder equation $x^2 + z^2 = r^2$:

$$    
(O_x + tD_x)^2 + (O_z + tD_z)^2 = r^2
$$

Expanding the squared terms results in:

$$    
(O^2_x + 2tO_xD_x + t^2D^2_x) + (O^2_z + 2tO_zD_z + t^2D^2_z) = r^2
$$

Simplify the terms:

$$    
O^2_x + O^2_z + t(2O_xD_x + 2O_zD_z) + t^2(D^2_x + D^2_z) = r^2
$$

And rearrange into the [quadratic equation](https://github.com/Busedame/miniRT/blob/main/README.md#quadratic-intersections-in-ray-tracing):

$$    
t^2(D^2_x + D^2_z) + t(2O_xD_x + 2O_zD_z) + (O^2_x + O^2_z - r^2) = 0
$$

Where the quadratic coefficients are: 

- $a = D^2_x + D^2_z$
- $b = 2O_xD_x + 2O_zD_z$
- $c = O^2_x + O^2_z - r^2$

