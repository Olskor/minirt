MiniRT

MiniRT is a simple ray tracer project developed as part of the curriculum at 42. The goal of this project is to create a basic ray tracing engine that can render 3D scenes. This project helps in understanding the fundamentals of computer graphics, particularly ray tracing, which is a rendering technique for generating realistic images by simulating the way light interacts with objects.
Features

- Render scenes with basic geometric shapes (spheres, planes, etc.)
- Implement lighting models including ambient, diffuse, and specular lighting
- Handle reflections for added realism
- Handle Disney's PBR shading
- Handle bumpmaps and textures
- support for basic .obj
- Parse scene descriptions from a configuration file

Getting Started
Prerequisites

Before you begin, ensure you have met the following requirements:

- You are using a Unix-like operating system (Linux, macOS)
- You have gcc or cc installed on your system
- You have make installed on your system

Installation

Clone this repository to your local machine:
    
    git clone https://github.com/yourusername/minirt.git

Navigate to the project directory:

    cd minirt

Compile the project:

    make

Usage

To render a scene, you need to provide a configuration file that describes the objects, lights, and camera settings in your scene.

Run the program with the following command:

    ./minirt scenes/scene.rt

Replace scenes/scene.rt with the path to your scene configuration file.
Example Scenes

Below are some example scenes rendered with MiniRT:
Example 1: Simple Sphere

Example 2: Multiple Objects

Example 3: Full Scene
![image](https://github.com/Olskor/minirt/assets/105324070/fa0a1052-bca6-4efd-8e63-b32de2efb4c9)


Contributing

Contributions are welcome! Please fork the repository and create a pull request with your changes.
License

This project is licensed under the MIT License. See the LICENSE file for more information.
Acknowledgements

    The 42 School for providing the project guidelines and resources
    Various online resources for tutorials and documentation on ray tracing techniques
