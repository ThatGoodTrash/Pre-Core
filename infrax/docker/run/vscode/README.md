# VSCode Remote-Container

The .devcontainer can be added to the root of your students-2022 project to easily use a dockerized version of the CNODP Wolves OS. The container that is built with the Dockerfile inclosed in the .devcontainer includes all of the tools required for CNODP pre-core. 

## Required Tools

1. Docker or Docker Desktop
2. VSCode
3. Remote-Container extension (installed in VSCode)

## Directions

1. Drop the .devcontainer folder into the root of your student project (remove any other .devcontainer folder that is present)
2. Ensure Docker or Docker Desktop is running
3. Enter the VScode command `Remote-Containers: Reopen Folder in Container` (use ctrl+shft+p for Windows/Liunux or cmd+shft+p for MacOS)
4. The docker build process should start, this may take a while depending on your internet connection! You can click on the pop up in the bottom right corner of the screen to view the build process
5. When the build process is complete, you should now be able to create a new terminal
6. Check to ensure that your username is "student" and your password is "student"

**NOTE:** If you have already been working in a remote container you will not start in your new container and will need to run the following command : `Remote-Containers: Rebuild Container`

**NOTE:** If you are having space issues there are other smaller versions of the container available. To use one of these you can comment out the top line of the Dockerfile inside .devcontainer and uncomment out the container version you would like. If you have already built the container you will need to run the `Remote-Containers: Rebuild Container` command in VSCode.