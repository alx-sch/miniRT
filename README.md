# miniRT

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/minirt_badge.png" alt="minirt_badge.png" />
</p>

This project is a collaboration between:

- **[Natalie](https://github.com/busedame)**: Responsible for the  `.rt` file parser and the implementation of lighting and shadows.
- **[Alex](https://github.com/alx-sch)**: Focused on MiniLibX (graphical library) integration, ray-object intersections, the renderer, and this README.

---

## Overview

- **[How to Use](https://github.com/Busedame/miniRT?tab=readme-ov-file#how-to-use)**: Building miniRT and defining scene elements in `.rt` files.
- **[Introduction to Ray Tracing](https://github.com/Busedame/miniRT/edit/main/README.md#introduction-to-ray-tracing)**
- **[Ray-Object Intersection](https://github.com/Busedame/miniRT/edit/main/README.md#ray-object-intersection)**: Explains the mathematics behind detecting ray intersections with geometric objects, forming the basis for functions used in miniRT.
  - [Ray Equation](https://github.com/Busedame/miniRT/edit/main/README.md#ray-equation)
  - [Quadratic Equation](https://github.com/Busedame/miniRT/edit/main/README.md#quadratic-equation)
  - [Plane Intersection](https://github.com/Busedame/miniRT/edit/main/README.md#plane-intersection)
  - [Sphere Intersection](https://github.com/Busedame/miniRT/edit/main/README.md#sphere-intersection)
  - [Cylinder Intersection](https://github.com/Busedame/miniRT/edit/main/README.md#cylinder-intersection)

---

## How to Use

1. Clone the repository and navigate into the project directory:    
   ```
   git clone https://github.com/Busedame/miniRT miniRT && cd miniRT
   ```
   
2. Build the project:
   ```
   make
   ```
   
3. **macOS Users:** Install X11 via XQuartz if needed:
   ```
   brew install xquartz
   ```
   If Homebrew is not installed, first run:
   ```
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```
   After installation, restart your Mac or run:
   ```
   export DISPLAY=:0
   ```
4. Run the program following the instructions in the output.

The `Makefile` automatically detects your OS and selects the correct MiniLibX library for compilation.
[MiniLibX](https://github.com/42Paris/minilibx-linux) is a simple graphics library for creating windows and handling graphics/events.

---

### Ray Tracing Files (.rt files)

Our miniRT implementation uses a left-handed coordinate system, meaning that increasing values of x move an object to the right, y moves it up, and z moves it away from the camera.
The `.rt` files define the elements and configurations for the scene to be rendered: 

#### Mandatory Elements

- **Ambient Light**  
  <img src="https://github.com/Busedame/miniRT/blob/main/.assets/rt_A.png" width="500" />  
  * **Identifier**: `A`  
  * **Ambient lighting ratio** (brightness, range: [0.0, 1.0]): `0.2`  
  * **Color** in RGB ([0-255]): `255, 255, 255`

- **Camera**  
  <img src="https://github.com/Busedame/miniRT/blob/main/.assets/rt_C.png" width="500"/>  
  * **Identifier**: `C`  
  * **Position (XYZ coordinates)**: `60, 0, 0`  
  * **Normalized orientation vector** (range: [-1.0, 1.0]): `1.0, 0.0, 0.0`  
  * **Field of view (FOV)** in degrees ([0-180]): `170`

- **Light**  
  <img src="https://github.com/Busedame/miniRT/blob/main/.assets/rt_L.png" width="500"/>  
  * **Identifier**: `L`  
  * **Position (XYZ coordinates)**: `90, 50, 70`  
  * **Lighting ratio** (brightness, range: [0.0, 1.0]): `0.7`  
  * *(Optional)* **Color** in RGB ([0-255]): `255, 255, 255` (default: white)

#### Optional Elements

- **Plane**  
  <img src="https://github.com/Busedame/miniRT/blob/main/.assets/rt_pl.png" width="500"/>  
  * **Identifier**: `pl`  
  * **Position (XYZ coordinates)** of a point on the plane: `0.0, 0.0, -500.0`  
  * **Normalized orientation vector** (range: [-1, 1]): `-1.0, 1.0, 1.0`  
  * **Color** in RGB ([0-255]): `0, 0, 225`

- **Sphere**  
  <img src="https://github.com/Busedame/miniRT/blob/main/.assets/rt_sp.png" width="500"/>  
  * **Identifier**: `sp`  
  * **Position (XYZ coordinates)** of the center: `90, 0.0, 0.0`  
  * **Diameter**: `60`  
  * **Color** in RGB ([0-255]): `0, 0, 255`

- **Cylinder**  
  <img src="https://github.com/Busedame/miniRT/blob/main/.assets/rt_cy.png" width="500"/>  
  * **Identifier**: `cy`  
  * **Position (XYZ coordinates)** of the center: `90.0, 0.0, 0.0`  
  * **Normalized orientation vector** (axis, range: [-1, 1]): `0.0, 1.0, 1.0`  
  * **Diameter**: `30`  
  * **Height**: `210.42`  
  * **Color** in RGB ([0-255]): `0, 0, 255`    

---
## Introduction to Ray Tracing

Ray tracing is a rendering technique that simulates the way light interacts with objects to create realistic images. Here, algorithms compute the color of each pixel by figuring out where the light came from for that pixel: By tracing the path of individual rays of light as they bounce off surfaces, it can produce highly detailed reflections, shadows, and global illumination.[¹](#footnote1)  

This method was popular in early static computer graphics —think of those iconic shiny spheres on checkerboard floors in 1980s / 1990s renders— but was somewhat niche due to its computational expense. However, with advancements in hardware, ray tracing is experiencing a renaissance in dynamic applications like real-time gaming, CGI, and architectural visualization.[¹](#footnote1)

This project, **miniRT**, aims to build a simple yet functional ray tracer from scratch in C, exploring the fundamentals of vector calculations and rendering.

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/ray_tracing_process.png" alt="ray_tracing_process.png" width="400"/>
    <br>
    <span><strong>Ray-tracing process:</strong> The ray goes from the camera through a pixel of the window and is tested for intersection with the objects. When a ray hits an object, the ray tracer works out how much light is reflected back along the ray to determine the pixel's color.<sup><a href="#footnote1">[1]</a></sup></span>
</p>
			     
<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/raytracing_example.png" alt="ray_tracing_example.png" width="400"/>
    <br>
    <span>Example of a ray-tracing render with matte and reflective objects.<sup><a href="#footnote2">[2]</a></sup></span>
</p>

---

## Introduction to basic mathematical terms

In this part, we will have a look at some important mathematical terms and concepts, needed to build the equations and calculations for miniRT.  
This part is written while studying the book "The Ray Tracer Challenge" by Jamis Buck, and it is a result of reading and taking notes from this book.

### Epsilon

Since we are dealing with floating point numbers (e.g. 1.5512) in our calculations, we need to account for floating point precision errors. This means that two numbers that should be seen as equivalent, can end up being shown as different. This happens because of round off errors happening on a binary level.  
To take this into consideration, we can use an `EPSILON` value. This is a very small value (e.g. 1-e6 or 0.000001).
```bash
	Instead of this:
	if (a < 0)

	Do this:
	if (a < EPSILON)
```

### Vectors

In a 3D space (as in the real world or in our miniRT), we can use a coordinate system to determine a *point in space*. This essentially means *where* something is located in a certain space.

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/coordinate_system.png" alt="coordinate_system.png" width="400"/>
    <br>
    <span>A coordinate system with x,y,z.<sup><a href="#footnote2">[2]</a></sup></span>
</p>

`x` How far to the right or the left.  
`y` How far up or down.  
`z` How close or far away from the viewer.  

A **vector** works similar, and can be seen as a line that's giving us information about two things:
- The direction it is pointing to.
- How long it is.

A vector gets determined by its x,y,z coordinates, as in a 3D coordinate system.
Since a vector needs two points to be defined, we can look at it like this:
- `start point` is (0,0,0)
- `vector point` is (2,4,1)
- To visualize how this works: Draw one point at 0,0,0 and draw a line to point 2,4,1. The direction of the vector will be determined by in which direction this line is going, starting from start point.

However, since these coordinates are also defining a *point* in a coordinate system, we need a way to distinguish a point from a vector. We can therefore add another variable, let's call it *w*.  
- `w` If it is a point (set to 1), if it is a vector (set to 0).  

##

**Adding a vector direction to a point➕**

Let's say we have a point a (2,5,-1,1) and a vector v(3,4,1,0). We want to figure out where you would be if you followed the direction of vector v, starting from point a. This essentially means that point a and point b together creates a vector that goes in the same direction as vector v. This follows the same logic as mentioned before, when drawing a vector.  
**We add the values of point a and vector together:**  
- a.x (2) + v.x (3) = b.x (5)
- a.y (5) + v.y (4) = b.y (9)
- a.z (-1) + v.z (1) = b.z (0)
- a.w (1) + v.w (0) = b.w (1)

And we are left with a new point b (5,9,0,1). Point (b) is in the direction of vector (v) from point (a) -- not from start point 0,0,0.

##

**Finding a vector direction between two points➖**

Let's say we have a point a (2,5,-1,1) and a point b (3,4,1,1). Since we are talking about miniRT, let's give them the following roles:
- `point a` = Light source coordinates.
- `point b` = Object coordinates.

We want to find a vector that gives us the direction from object to light source.  
The direction of a vector between two points can be seen as this formula:
```bash
	direction (x,y,z,0) = dest (x,y,z,1) - origin (x,y,z,1)
```
**We subtract the values of point b from point a == light_coords - object_coords == a - b.**  
- a.x (2) - b.x (3) = v.x (-1)
- a.y (5) - b.y (4) = v.y (1)
- a.z (-1) - b.z (1) = v.z (-2)
- a.w (1) - b.w (1) = v.w (0)

In order to make the vector point from the object to the light source, subtract the object’s coordinates from the light source’s coordinates. This way, the vector will point in the direction from the object to the light source.

💡 Note: If you picture every vector to start from coordinates (0,0,0). If a vector has the coordinates (2,4,2) - it shows that everytime the vector moves -- move 2 positions to the right, 4 positions up and 2 positions away from you. With this example: Draw a line between point1 (0,0,0) and point2 (2,4,2).  
**So:** In the above example of having two points (a and b) and creating a vector, the vector is going to tell us "how to move" from one point to ultimately reach the other point.

##

**Finding the opposite direction of a vector🔃**

Say we have a vector pointing from a surface to the light source. What can we do to reverse the direction -- so make it point *from* the light source *to* the surface?  
**We introduce a zero vector (0,0,0,0) subtract vector v (2,4,1,0) from vector zero, and get new vector:**  
- zv.x (0) - v.x (2) = nv.x (-2)
- zv.y (0) - v.y (4) = nv.y (-4)
- zv.z (0) - v.z (1) = nv.z (-1)
- zv.w (0) - v.w (0) = nv.w (0)

Here we are essentially just reversing the *sign* of the different coordinates of vector v. Another (and much more straightforward) way to do this, would be just reversing the sign of vector v. **So + becomes -, and - becomes +**.

##

**Finding the distance from start to a point🏃‍♀️**

If you have a vector, and you want to find a point that is 3.5 times further in the vector direction, e.g. to see where a ray intersects a sphere. 3.5 would be the *scalar* value. Multiplying with this value, *scales* the vector - meaning that each component (x,y,z,w) gets multiplied with the same value (3.5).  
**We have a vector v (2,-1,3) and scale it by 3.5:**  
- v.x (2) * 3.5 = 7
- v.y (-1) * 3.5 = -3.5
- v.z (3) * 3.5 = 10.5

The result after scaling gives us a point (7,-3.5,10.5). This point will be 3.5 times further away from our original point, moved in the direction of vector v.

##

**Finding the length of a vector📏**

Until now, we have mainly looked at different ways to figure out vector directions. Now, what about the length, or the *magnitude* of a vector? This means how far you would travel in a straight line, if you were to walk from one end of the vector to the other.  

Do you remember Pythagoras' theorem?  

$$
a² + b² = c²
$$

We have a vector v (1, 2, 3). The equation would look like this -> 1² + 2² + 3² = x²:
- v.x (1) = 1 * 1 = 1
- v.y (2) = 2 * 2 = 4
- v.z (3) = 3 * 3 = 9
- 1 + 4 + 9 = 14
- Since 14 is equivalent to x², and we want to find x, we need to take the *square root* of 14.
- The magnitude of vector v is 3.741657387.

In our miniRT project, we don't want to operate with vectors with a different magnitude than 1. These vectors are called *unit vectors*. If we don't work with unit vectors - if we don't use *normalized* vectors - the calculations would be scaled differently for every ray casted. By using normalized vectors, all calculations will be done relative to a common scale (the unit vector which is 1).

**Normalization⚖️**

Normalizing a vector keeps the correct direction, but reduces or increases its magnitude to 1. In miniRT we don't accept orientation vectors that are not normalized, but whenever a new vector is created - we make sure to normalize it each time.  
You normalize a vector by dividing each of its components by its magnitude.
- We have a vector v (1,2,3) and after using Pythagoras' theorem (multiplying each value with itself one time, adding them together, then square root of the result), we figured out its magnitude is 3.741657387.
- We divide each of its components by the magnitude (1 / 3.741657387, 2 / 3.741657387, 3 / 3.741657387).
- Vector v now has the following coordinates (0.267261242, 0.534522484, 0.801783726)
- Now let's check if vector v is now normalized, by using Pythagoras' on these new values.
- 0.071428571 + 0.285714286 + 0.642857143 = 1
- Since the square root of 1 = 1, the vector v is now normalized.

###

---

## Ray-Object Intersection

This section outlines the mathematical approach to detecting intersections between rays and various geometric objects. While this [overview document](https://github.com/josephcheel/42-MiniRT/blob/87dd9a09ded69ea9fbc0ae50bf085517908b9f85/Resources/Math/Intersection%20points%20calculations.pdf) was not directly used for deriving all the mathematical formulations and functions presented here, it provides an excellent summary of the fundamental concepts and calculations.

### Ray Equation

A ray is represented as:

$$
P(t) = O + t \vec{d}
$$

Where:
- **$P(t)$:**  The point on the ray at distance $(t)$ from the ray's origin. It represents a location along the path defined by the ray, calculated by moving from the ray's starting point in the direction of the ray's direction vector.

- **$O$:**  The ray's origin in 3D space. This point marks the location where the ray begins its journey through space (camera).

-  **$\vec{d}$:** The normalized direction vector of the ray. A normalized vector has a magnitude (or length) of 1, ensuring that the scalar $(t)$ directly corresponds to the distance traveled along the ray.  

- **$t$:**  A scalar value indicating the distance along the ray. It scales the direction vector, determining how far along the ray the point $P(t)$ is. When the direction vector is normalized, the value of $(t)$ directly represents the magnitude of the distance from the ray’s origin.

---

### Plane Intersection

To find the intersection of a ray with a plane, we use the plane equation:

$$
(P - P_0) \cdot \vec{n} = 0
$$

Where:
- **$P$:** Is any point on the plane.
- **$P_0$** Is a known point on the plane 
- **$\vec{n} $:** The normal vector of the plane, which is perpendicular to the surface.

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/plane_definition.png" alt="plane_definition.png" width="200"/>
    <br>
    <span>A plane is defined by a point <i>a</i>, which determines its location, and a normal <i>n</i>, which defines its orientation. The point <i>p</i> is any point on the plane, such as the intersection of a ray with the plane.<sup><a href="#footnote1">[1]</a></sup></span>
</p>

Substitute the ray equation $P(t) = O + t \vec{d}$ into the plane equation:

$$
(O + t \vec{d} - P_0) \cdot \vec{n} = 0
$$

Rearrange terms:

$$
(O - P_0) \cdot \vec{n} + t (\vec{d} \cdot \vec{n}) = 0
$$

Solve for *t*:

$$
t = \frac{(P_0 - O) \cdot \vec{n}}{\vec{d} \cdot \vec{n}}
$$

- ($t$) will be **positive** if the denominator $(\vec{d} \cdot \vec{n} )$ is positive, meaning that the ray is moving **towards** the plane. The ray will intersect the plane **in front of the camera**.
- ($t$) will be **negative** if the denominator $(\vec{d} \cdot \vec{n})$ is negative, meaning that the ray is moving **away** from the plane. The ray will intersect the **behind the camera**.
- If the denominator $(\vec{d} \cdot \vec{n} )$ is zero  (*t* is undefined or infinite), it means the ray is **parallel** to the plane and does not intersect it.

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/ray_plane_intersection.png" alt="ray_plane_intersection.png" width="400"/>
    <br>
    <span>The plane becomes visible if the ray intersects it in front of the camera's origin (t > 0).<sup><a href="#footnote1">[1]</a></sup></span>
</p>

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
		if (*t > 0.0)
			return (1);
	}

	return (0);	// No valid intersection is found
}
```
---

### Quadratic Equation

While planes are intersected by solving a linear equation, objects like spheres and cylinders require solving a **quadratic equations**. A quadratic equation has the general form:

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

---

### Sphere Intersection

To find where a ray intersects a sphere, we start with the general equation of the sphere:

$$
\Vert P - C \Vert^2= \left( P  - C \right) \cdot \left(P - C \right) = r^2
$$

Where:
- **$P$:** Is any point on the sphere's surface.
  
- **$C$:** The center of the sphere.
  
- **$r$:** The radius of the sphere.

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/sphere_definition.png" alt="sphere_definition.png" width="200"/>
    <br>
    <span> A sphere is defined by its center <i>c</i> and radius <i>r</i>, which determine its size and position. The point <i>p</i> represents any point on the sphere's surface (potential intersection point).<sup><a href="#footnote1">[1]</a></sup></span>
</p>

Now, substitute the ray equation $P(t) = O + t \vec{d}$ into the sphere equation:

$$
\left(O + t \vec{d} - C \right) \cdot \left( O + t \vec{d} - C \right) = r^2
$$

Let $\vec{oc} = O - C$, the vector from the sphere center to the ray origin. The equation becomes:

$$
\left(\vec{oc} + t \vec{d} \right) \cdot \left( \vec{oc} + t \vec{d} \right) = r^2
$$

Expand the dot product:

$$
\left( \vec{oc} \cdot \vec{oc} \right) + 2t \left( \vec{oc} \cdot \vec{d} \right) + t^2 \left( \vec{d} \cdot \vec{d} \right) = r^2
$$

Since $\vec{d}$ is normalized ($\Vert \vec{d} \Vert=  \vec{d} \cdot \vec{d} = 1$), the equation simplifies into an quadratic equation: 

$$
t^2 +  2t \left( \vec{oc} \cdot \vec{d} \right) + \left( \vec{oc} \cdot \vec{oc} \right) - r^2 = 0
$$

As explained [above](https://github.com/Busedame/miniRT/blob/main/README.md#quadratic-intersections-in-ray-tracing), this solves into:

$$
t = \frac{-b \pm \sqrt{b^2 - 4c}}{2}
$$

Where the coefficients are:

- **$a = 1$**
- **$b = 2(\vec{oc} \cdot \vec{d}$)**
- **$c = (\vec{oc} \cdot \vec{oc}) - r^2$**

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/ray_sphere_discriminante.png" alt="ray_sphere_discriminante.png" width="400"/>
    <br>
    <span>The discriminant indicates whether the ray intersects the sphere at zero, one, or two points.<sup><a href="#footnote1">[1]</a></sup></span>
</p>

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/ray_sphere_intersection_distance.png" alt="ray_sphere_intersection_distance.png" width="400"/>
    <br>
    <span>Rays do not register an intersection at their origin; the intersection requires t > 0.<sup><a href="#footnote1">[1]</a></sup></span>
</p>

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
	if (*t > 0.0)
		return (1);

	// Calculate the distance to the second intersection point (largest root)
	*t = calculate_exit_distance(1.0, b, discriminant);

	// Check if the exit point is valid (distance must be non-negative)
	if (*t > 0.0)
		return (1);

	return (0);	// No valid intersection found
}
```

---

### Cylinder Intersection

For a cylinder with:
- a center point $C=(C_x, C_y, C_z)$ through which the cylinder's axis passes,
- radius $r$,
- and a normalized orientation vector $\vec{u}$, which represents the direction of the cylinder's axis,

the general equation for a point $P=(P_x, P_y, P_z)$ on the surface of the cylinder is:

$$    
(P_x - C_x)^2 + (P_y - C_y)^2 + (P_z - C_z)^2 - \left( (P_x - C_x,  P_y - C_y,  P_z - C_z) \cdot \vec{u}\right)^2 = r^2
$$

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/cylinder_definition.png" alt="cylinder_definition.png" width="200"/>
    <br>
    <span>A cylinder is defined by a point on its axis and a vector representing its direction (e.g., <i>(0,0,0)</i> as the point and <i>(0,1,0)</i> as the orientation vector along the y-axis in the figure above in the figure above), a radius, and a height given by $\Vert y_1 - y_0 \Vert$. The point  <i>p</i> can be any point on the cylinder's mantle.<sup><a href="#footnote1">[1]</a></sup></span>
</p>

Now define the vector from the reference point ($C$) (on the axis) to the point ($P$) (on the surface), which captures the spatial relationship between the axis and the surface point:

$$    
\vec{p} = (P_x - C_x,  P_y - C_y,  P_z - C_z)
$$

- $(P_x - C_x)^2 + (P_y - C_y)^2 + (P_z - C_z)^2 = \Vert\vec{p}\Vert^2$: The square of the distance from the axis reference point $C$ to the surface point $P$.
- $(\vec{p} - \vec{u})^2$: The squared projection of $\vec{p}$ onto the axis direction $\vec{u}$, which measures the component of $\vec{p}$ along the cylinder's axis.
- Subtracting $(\vec{p} - \vec{u})^2$ removes the contribution of $\vec{p}$ along the axis, leaving only the radial distance from the axis.

The cylinder’s surface is defined by ensuring the perpendicular (radial) distance from the axis equals the radius ($r$). The following equation ensures that this condition is met:

$$
\Vert \vec{p} \Vert^2 - (\vec{p} \cdot \vec{u})^2 = r^2
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
\left(\vec{oc} +t\vec{d}\right)^2 - \left(\vec{u} \cdot \vec{oc} + t( \vec{u} \cdot \vec{d})\right)^2 = r^2
$$

Let ($\text{axis-dot-oc} = \vec{u} \cdot \vec{oc}$) and ($\text{axis-dot-ray} = \vec{u} \cdot \vec{d}$):

$$
\left(\vec{oc} +t\vec{d}\right)^2 - \left(\text{axis-dot-oc} + t(\text{axis-dot-ray})\right)^2 = r^2
$$

Expanding the two squared terms gives:

$$
\left( \vec{oc} \cdot \vec{oc} + 2t(\vec{oc} \cdot \vec{d}) + t^2(\vec{d} \cdot \vec{d})\right) - \left( (\text{axis-dot-oc})^2 + 2t(\text{axis-dot-oc} \times \text{axis-dot-ray}) + t^2(\text{axis-dot-ray})^2 \right)
$$

Expanding the squared terms of the **second part** of the equation gives:

$$
\text{axis-dot-oc}^2 + 2t(\text{axis-dot-oc} \times \text{axis-dot-ray}) + t^2(\text{axis-dot-ray})^2
$$

Grouping all this into a quadratic form ($at^2+bt+c=0$) gives the following coefficients:

- $a = (\vec{d} \cdot \vec{d}) - (\text{axis-dot-ray})^2$

- $b = 2\left( (\vec{oc} \cdot \vec{d}) - (\text{axis-dot-oc} \times \text{axis-dot-ray})\right)$

- $c = (\vec{oc} \cdot \vec{oc}) - (\text{axis-dot-oc})^2 - r^2$

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
	if (*t > 0.0)
		return (1);

	// Calculate the exit distance along the ray (second root of the quadratic)
	*t = calculate_exit_distance(cylinder->ixd.a, cylinder->ixd.b, cylinder->ixd.discriminant);

	// Check if the exit point is valid (distance must be non-negative)
	if (*t > 0.0)
		return (1);

	return (0);	// No valid intersection found
}
```
Please note that this function calculates the intersection of a ray with an infinite cylinder, not yet considering the cylinder's height and end caps. So far, it only detects intersections with the cylinder's lateral surface:

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/scene_no_height.png" alt="scene_no_height.png" width="500"/>
    <br>
    <span>The blue and red objects are both infinite cylinders.</span>
</p>

---

#### Handling the Cylinder's Height

To account for the height boundaries of the cylinder, follow these steps:

1. **Find the intersection point:**    
   Use the ray equation with the calculated intersection distance ($t$) to find the intersection point ($P$):
   
$$
P(t) = O + t \vec{d}
$$

2. **Compute vector from cylinder's center to intersection point:**

$$
\vec{v} = P - C
$$

3. **Project this vector onto the cylinder's axis:**       
   Find the component of ($\vec{v}$) along the cylinder's axis by projecting ($\vec{v}$) onto the normalized axis direction vector ($\vec{u}$):

$$
\text{Projection Length} = \vec{v} \cdot \vec{u}
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
	if (*t > 0.0 && check_cylinder_height(ray_origin, ray_dir, *t, cylinder))
		return (1);

	// Calculate the exit distance along the ray
	*t = calculate_exit_distance(cylinder->ixd.a, cylinder->ixd.b, cylinder->ixd.discriminant);

	// Check if the exit point is valid and lies within the cylinder's height bounds
	if (*t > 0.0 && check_cylinder_height(ray_origin, ray_dir, *t, cylinder))
		return (1);

	return (0);	   // No valid intersection found
}
```
<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/scene_no_caps.png" alt="scene_no_caps.png" width="500"/>
    <br>
    <span>The blue and red cylinders are finite in height but have no caps. Looking through the blue cylinder.</span>
</p>

---

#### Accounting for End Caps

To account for the cylinder's end caps, the goal is to check if a ray intersects the circular regions at the top or bottom of the cylinder. These regions can be treated as planes with finite radii. The steps to determine an intersection with a cap are as follows:

1. **Represent the cap as a plane**:  
   Each cap is a circular disk on a plane perpendicular to the cylinder's axis. The plane equation for a cap is: $(P - C_{\text{cap}}) \cdot \vec{U} = 0$

   Here:
   - $(P)$ is a point on the plane (we will test for the ray-cap intersection).
   - $(C)$ is the center of the cap (top or bottom).  
   - $\(\vec{u}\)$ is the normalized orientation vector of the cylinder's axis.  

3. **Find the ray-plane intersection:**     
   Substitute the ray equation into the plane equation: $( O + t \vec{d} - C_\text{cap} ) \cdot \vec{u} = 0$

   Where:
   - $(O)$ is the ray origin.  
   - $(\vec{d})$ is the normalized direction vector of the ray
   - $(t)$ is the distance from $(O)$ to the intersection point.

   Simplify: $\left(\vec{oc}_\text{cap} \cdot \vec{u} + t(\vec{d} \cdot \vec{u}) \right) = 0$

   Solve for $t = - \frac{\vec{oc}_\text{cap} \cdot \vec{u}}{\vec{d} \cdot \vec{u}}$

4. **Check the intersection point against the cap's radius:**    
   Once ($t$) is computed, the intersection point $(P(t))$ can be calculated using the ray equation.
   The intersection point lies within the cap if the squared length of this vector is less than or equal to the squared radius of the cap:
   $\Vert P(t) - C_{\text{cap}}  \Vert^2 \leq r^2$

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
	t_vec3	cap_center;	// Center of the cap being checked
	t_vec3	cap_normal;	// Normal vector of the cap
	double	denominator;	// fraction's denominator: dot product of ray direction and cap normal;
	double	numerator	// fraction's numerator: dot product of OC-vec and cap normal
	double	t_hit;		// Distance to the intersection point (ray x cap) along the ray
	t_vec3	p_hit;		// Computed intersection point on the cap
	t_vec3	difference;	// Vector from cap center to intersection point

	// Determine cap center and normal based on the flag
	if (flag_top)
	{
		// Top cap: offset cylinder center by half its height along the orientation
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
	denominator = vec3_dot(ray_dir, cap_normal);

	// If the denominator is near zero, the ray is parallel to the cap and cannot intersect
	if (fabs(denominator) < 1e-6)
		return (0);

	// Calculate the distance t_cap to the intersection point on the cap plane
	numerator = vec3_dot((vec3_sub(ray_origin, cap_center), cap_normal));
	t_hit = - numerator / denominator;

	// If the intersection is behind the ray's origin, discard it
	if (t_hit <= 0.0)
		return (0);

	// Compute the actual intersection point in 3D space
	p_hit = vec3_add(ray_origin, vec3_mult(ray_dir, t_hit));

	// Check if the intersection point lies within the cap's radius
	difference = vec3_sub(p_hit, cap_center);
	if (vec3_dot(difference, difference) <= (cyl->radius * cyl->radius))
	{
		// Valid intersection: store the distance and return success
		*t = t_hit;
		return (1);
	}
	return (0);	// No valid intersection within the cap's radius
}
```

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/scene_complete_cyl.png" alt="scene_complete_cyl.png" width="500"/>
    <br>
    <span>Looking at the end cap of the closed blue cylinder.</span>
</p>

---

## Perspective Viewing

<p align="center">
    <img src="https://github.com/Busedame/miniRT/blob/main/.assets/orthographic_perspective_viewing.png" alt="orthographic_perspective_viewing.png" width="500"/>
    <br>
    <span><strong>Top:</strong> In orthogonal viewing, each pixel is a separate camera ray, all running parallel to one another. This results in objects being the same size, regardless of their distance. Used in technical drawings and CAD. <br><strong>Bottom:</strong> Perspective viewing is more in line with how we perceive the world: Camera rays have a single point of origin. This way, objects have a vanishing point and appear smaller the farther they are away. Used in realistic 3D rendering. <br> Sources: Diagrams left <sup><a href="#footnote1">[1]</a></sup>; diagrams right<sup><a href="#footnote3">[3]</a></sup> </span>
</p>

### The Geometry of Perspective Projection

A **pinhole camera model** can be used to describe how a 3D scene is projected onto a 2D screen (viewport). The pinhole model has the following properties
- Rays originate from the camera's position (the "eye") and pass through a virtual screen plane (the viewport).
- The **field of view (FOV)** defines the angular range visible to the camera, which determines the extent of the scene captured.
- The **view frustum** is a truncated pyramid extending from the camera's position toward the viewport. The rectangular screen at the base of the frustum defines the visible scene.

<p align="center">
	<img width="600" alt="FOV_frustum" src="https://github.com/Busedame/miniRT/blob/main/.assets/FOV_frustum.png">  
	<br>
	<span>Pinhole camera model illustrating the FOV frustum and the rectangular screen for 2D projection (viewport).</span>
</p>

<p align="center">
	<img width="350" alt="Viewpoint_FOV" src="https://github.com/Busedame/miniRT/blob/main/.assets/Viewport_Field_of_View.png">
	<br>
	<span>Top: Camera's FOV viewed from above. Bottom: 2D projection onto the screen.</span>
</p>

---

### Ray Direction Calculation

The **Field of View (FOV)** represents how much of the 3D scene is visible to the camera. Depending on the orientation of the camera, the FOV could be horizontal or vertical:

- The vertical FOV ($\text{FOV}_v$) is the angle between the top and bottom edges of the view frustum.
- The horizontal FOV ($\text{FOV}_h$) is the angle between the left and right edges of the view frustum.

Vertical FOV is often the most common in graphics programming, but horizontal FOV can also be defined depending on the viewport dimensions.

We employ trigonometric functions, specifically the tangent function, to calculate how this FOV scales the projection from 3D space onto 2D screen space.

---

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

In C, trigonometric functions expect their input angles to be in radians, not degrees. Therefore, the FOV angle is converted using the formula $Radians = Degrees \times \frac{\pi}{180}$ in the function for ray direction calculation below.

---

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
The z-component of the ray direction is conventionally set to 1.0
This positions the projection plane (or screen) at z = 1.0 in camera space, simplifying the
perspective projection calculations. The resulting vector is then normalized to ensure it has
a unit length, making it independent of the initial choice for the z-component.
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

---

### Handling Camera Orientation

In a ray-tracing system, the camera's orientation defines how the rays originating from the camera are aligned with the 3D scene. To compute ray directions in world space, you must transform the rays from camera space, where the z-axis points forward, to the orientation defined by the camera's position and rotation in the scene.

#### Camera Orientation Vectors

The camera's orientation in 3D space is defined by three mutually orthogonal vectors:

- `cam_right`: Points to the right of the camera's view (x-axis).
- `cam_up`: Points upward from the camera's perspective (y-axis).
- `cam_orientation` (provided by .rt file): Points forward along the camera's line of sight (z-axis).

These vectors form a **basis** for the camera's local coordinate system. To transform a direction vector from camera space to world space, you combine these basis vectors weighted by the direction's components in camera space.

#### Steps for Orientation Transformation

1. Calculate the Ray Direction in Camera Space:    
   The ray direction in camera space is computed from the pixel's normalized coordinates and the field of view, as shown in the earlier function above:
   - $\text{ray-cam-dir} = (x', y', z')$, where:
      - ($x'$): Scaled and aspect-ratio-adjusted horizontal NDC coordinate.
      - ($y'$): Scaled vertical NDC coordinate.
      - ($z'$): Always 1.0, pointing forward in camera space
    
2. Transform the Ray Direction in Camera Space to World Space:    
   After calculating the ray's direction in camera space, we need to transform this direction into world space, where the entire 3D scene is defined. The formula for this transformation is:
   - $\text{ray-world-dir} = (x' \times cam-right) + (y' \times cam-up) + (z' \times cam-orientation)$

3. Normalize the Resulting Vector:
   To ensure that the ray direction is a unit vector, normalize the resulting world-space vector.

This full implementation of the `compute_ray_direction` function incorporates the camera orientation:

```C
/**
Function to compute the ray direction for a given pixel in a camera's view,
considering the camera's field of view (FOV), aspect ratio, and orientation.

 @param x		The horizontal pixel coordinate on the screen.
 @param y		The vertical pixel coordinate on the screen.
 @param cam		The camera object containing the FOV, orientation vector, and position.

 @return		The normalized direction vector of the ray passing through the pixel, in world space.
*/
static t_vec3	compute_ray_direction(int x, int y, t_cam cam)
{
	double	scale;		// Scaling factor from the vertical FOV
	double	aspect_ratio;	// Ratio of screen width to height
	double	norm_x;		// Normalized x-coordinate in NDC
	double	norm_y;		// Normalized y-coordinate in NDC
	t_vec3	cam_right;	// The rightward direction vector of the camera in world space
	t_vec3	cam_up;		// The upward direction vector of the camera in world space
	t_vec3	ray_cam_dir;	// The direction vector of the ray in camera space
	t_vec3	ray_world_dir;	// The direction vector of the ray in world space

	scale = tan((cam.fov / 2) * M_PI / 180.0);

	aspect_ratio = (double)WINDOW_W / (double)WINDOW_H;

	// Map pixel coordinates to normalized device coordinates (NDC)
	norm_x = ((2.0 * (x + 0.5) / WINDOW_W) - 1.0) * aspect_ratio * scale;
	norm_y = (1.0 - (2.0 * (y + 0.5) / WINDOW_H)) * scale;

	// Ray direction in camera space
	ray_cam_dir = vec3_new(norm_x, norm_y, 1.0);

	// The cross product produces a vector that is orthogonal to both input vectors.
	cam_right = vec3_norm(vec3_cross(vec3_new(0, 1, 0), scene->cam.ori)); 
	cam_up = vec3_norm(vec3_cross(scene->cam.ori, scene->cam.right));

	// Transform the ray direction in camera space to world space:   
	ray_world_dir = vec3_add(
				vec3_add(
					vec3_mult(cam.right, ray_cam_dir.x),
					vec3_mult(cam.up, ray_cam_dir.y)),
				vec3_mult(cam.ori, ray_cam_dir.z));

	return (vec3_norm(ray_world_dir)); // Return normalized ray direction vector in world space
}
```

## Acknowledgements

The amazing book *Ray Tracing from the Ground Up* by Kevin Suffern is not only an excellent and exhaustive resource on the subject, but also an easy-to-follow guide to the concepts and mathematics behind ray tracing. Figures taken from this book are quoted accordingly. [¹](#footnote1)

The project badge used is retrieved from [this repo](https://github.com/ayogun/42-project-badges) by Ali Ogun.

## References

<a name="footnote1">¹</a> Suffern, K. (2007). *Ray Tracing from the Ground Up*. A K Peters.     
<a name="footnote2">²</a> Jensen, H.W. (1990-1991): [http://graphics.ucsd.edu/~henrik/images/raytrace.html](http://graphics.ucsd.edu/~henrik/images/raytrace.html)    
<a name="footnote3">³</a> Datamine Software (2024). *Perspective and Orthogonal Views*: [https://docs.dataminesoftware.com/StudioEM/Latest/VR_Help/Perpective%20and%20Orthogonal%20Modes.htm](https://docs.dataminesoftware.com/StudioEM/Latest/VR_Help/Perpective%20and%20Orthogonal%20Modes.htm)
