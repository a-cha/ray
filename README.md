# Ray Tracing

###### _My first RayTracer written in C99_

The program can render several figures with multiple light sources.

<img width="700" src="https://user-images.githubusercontent.com/81406370/121876671-71f63b80-cd12-11eb-98e7-e74db918018d.gif">

## Usage

Run `make` inside the repository's directory to build `miniRT` binary. 

Program needs the path to configuration file as an argument (examples in **scenes** directory). If flag `--save` is presented as a second argument, program will make a screenshot and save it in the working directory. 

<details>
    <summary>
        Setting up the configuration file
    </summary>
    <br/>
    <p>You can specify what figures to render (<i>plane</i>, <i>sphere</i>, <i>square</i>, <i>cylinder</i> and <i>triangle</i> available), several light sources and points of view.</p>
    <p><b>General scene settings:</b></p>
    <ul>
        <li>Window resolution &emsp;&emsp; 
            <sub>
                <i>R &emsp;1280&emsp; 1920</i>
            </sub>
        </li>
        <li>Ambient light (brightness, colour) &emsp;&emsp; 
            <sub>
                <i>A &emsp;0.6 &emsp;255,255,255</i>
            </sub>
        </li>
        <li>Cameras (coordinates, direction, viewing angle) &emsp;&emsp; 
            <sub>
                <i>c &emsp;1.4,0,-1 &emsp;0,0,1 &emsp;70</i>
            </sub>
        </li>
        <li>Light sources (coordinates, brightness, colour) &emsp;&emsp; 
            <sub>
                <i>l &emsp;7,7,4 &emsp;0.3 &emsp;255,255,255</i>
            </sub>
        </li>
    </ul>
    <p><b>Figure's settings:</b></p>
    <ul>
        <li>Plane (coordinates, direction, colour) &emsp;&emsp; 
            <sub>
                <i>pl &emsp;2,-1.3,0 &emsp;0,1,0 &emsp;245,245,245</i>
            </sub>
        </li>
        <li>Sphere (coordinates, radius, colour) &emsp;&emsp; 
            <sub>
                <i>sp &emsp;3.2,-0.8,-1.4 &emsp;0.4 &emsp;60,60,60</i>
            </sub>
        </li>
        <li>Square (coordinates, direction, width, colour) &emsp;&emsp; 
            <sub>
                <i>sq &emsp;-0.2,0.5,-2.35 &emsp;1,0,0 &emsp;0.7 &emsp;37,245,123</i>
            </sub>
        </li>
        <li>Cylinder (coordinates, direction, width, height, colour) &emsp;&emsp; 
            <sub>
                <i>cy &emsp;0,0,0 &emsp;0,1,0 &emsp;1 &emsp;2 &emsp;70,90,225</i>
            </sub>
        </li>
        <li>Triangle (coordinates for each angle, colour) &emsp;&emsp;
            <sub>
                <i>tr &emsp;1.5,0.2,2.58 &emsp;3.2,0.4,3 &emsp;2.3,2,4.1 &emsp;255,109,36</i>
            </sub>
        </li>
    </ul>
</details>
