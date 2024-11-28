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
P(t) = \text{ray-origin} + t \times \text{ray-dir}
$$

Where:
- **P(t):**  
    The point on the ray at distance \(t\) from the ray's origin.  
    It represents a location along the path defined by the ray, calculated by moving from the ray's starting point in the direction of the ray's direction vector.

- **ray-origin:**  
    The starting point of the ray, represented as a 3D vector.  
    This point marks the location where the ray begins its journey through space (camera).

- **ray-dir:**  
    The normalized direction vector of the ray.  
    A normalized vector has a magnitude (or length) of 1, ensuring that the scalar \(t\) directly corresponds to the distance traveled along the ray.  
    The direction vector defines the ray's path, indicating the direction in which the ray travels.

- **t:**  
    A scalar value indicating the distance along the ray.  
    It scales the direction vector, determining how far along the ray the point \( P(t) \) is. When the direction vector is normalized, the value of \(t\) directly represents the magnitude of the distance from the ray’s origin.

### Plane Intersection

To find the intersection of a ray with a plane, we use the plane equation:

$$
\text{plane-normal} \cdot (P(t) - \text{plane-point}) = 0
$$

Where:
- **plane-normal:**  
    The normal vector of the plane, which is perpendicular to the surface.
- **plane-point:**  
    Any point on the plane.

Substitute the ray equation ' $P(t) = \text{ray-origin} + t \times \text{ray-dir}$ ' into the plane equation:

$$
\text{plane-normal} \cdot (\text{ray-origin} + t \times \text{ray-dir} - \text{plane-point}) = 0
$$

Simplify this expression to find *t*:

$$
t = \frac{\text{plane-normal} \cdot (\text{plane-point} - \text{ray-origin})}{\text{plane-normal} \cdot \text{ray-dir}}
$$

- *t* will be **positive** if the denominator ' $\text{plane-normal} \cdot \text{ray-dir}$ ' is positive, meaning that the ray is moving **towards** the plane. The ray will intersect the plane **in front of the camera**.
- *t* will be **negative** if the denominator ' $\text{plane-normal} \cdot \text{ray-dir}$ ' is negative, meaning that the ray is moving **away** from the plane. The ray will intersect the **behind the camera**.
- If the denominator ' $\text{plane-normal} \cdot \text{ray-dir}$ ' is zero  (t is undefined or infinite), it means the ray is **parallel** to the plane and does not intersect it.

Since we only consider the **field of view (FOV) frustum**, which is in front of the camera, it suffices to check if the denominator ' $\text{plane-normal} \cdot \text{ray-dir} > 0$ ' to determine if the ray intersects the plane **in the scene**.
