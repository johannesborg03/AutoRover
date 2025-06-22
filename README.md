# 2025-group-14: Autonomous Cone Detection & Steering Control

**Members:** Lilly Heier, Daniel Norberg, Erik Gabrielsson, Johannes Borg

## Badges

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Visuals](#visuals)
- [Getting Started](#getting-started)
- [Building and Running](#building-and-running)
- [Docker Usage](#docker-usage)
- [Data Analysis & Evaluation](#data-analysis--evaluation)
- [Project Structure](#project-structure)
- [Development Workflow](#development-workflow)
- [Authors & Acknowledgments](#authors--acknowledgments)
- [License](#license)

---

## Project Overview
This project is developed as part of the DIT638 course at Chalmers University. It demonstrates real-time cone detection and steering angle computation for autonomous vehicles using computer vision (OpenCV) and the OpenDLV platform. The system processes shared memory images, detects cones, computes steering angles, and logs results for evaluation.

---

## Features
- **Cone Detection:**
  - Detects blue and yellow cones in real-time using HSV color segmentation and contour analysis (OpenCV).
  - Limits and sorts detected cones for robust downstream processing.
- **Steering Angle Calculation:**
  - Computes steering wheel angle from angular velocity using a scaling and limiting algorithm.
- **Integration with OpenDLV:**
  - Attaches to shared memory and communicates with OD4 sessions for message exchange.
- **Data Analysis Scripts:**
  - Python scripts for log formatting and steering angle evaluation.
- **Visualization:**
  - Gnuplot scripts and CSVs for comparing computed and ground truth steering angles.

---

## Visuals
- Example plot: `src/algorithm/SteeringAngle/Rec1_plot.png` shows ground truth vs. computed steering angles.
- To generate/update plots, use the provided `.gnu` script with Gnuplot and the corresponding CSV files.

---

## Getting Started
### Prerequisites
- **C++17** or newer
- **CMake** (>=3.2)
- **OpenCV** (core, highgui, imgproc)
- **Docker** (optional, for containerized builds)
- **Python 3** (for data analysis scripts)

### Clone the Repository
```sh
git clone git@git.chalmers.se:courses/dit638/students/2025-group-14.git
cd 2025-group-14
```

---

## Building and Running
### Build with CMake
```sh
mkdir build
cd build
cmake ..
make
```

### Run the Main Application
The main executable is built from `src/template-opencv.cpp` and integrates cone detection and steering logic.

**Example usage:**
```sh
./template-opencv --cid=253 --name=img --width=640 --height=480 --verbose
```
- `--cid`: OD4 session ID
- `--name`: Shared memory area name
- `--width`, `--height`: Image dimensions
- `--verbose`: (Optional) Show live OpenCV window

---

**We have a Dockerfile to build docker image of our project.**  
To build a Docker image of our project enter:    
docker build -t dit639_group14 .    
And to run it, enter:           
docker run dit639_group14 4    // (4 is argument for main source file)  
  
## Workflow

### Issue Creation  
For each new feature or fix, we will create an **issue** that includes:  

- **Purpose**: A clear description of what needs to be done.  
- **Acceptance Criteria**: Conditions that must be met for the issue to be considered complete.  
- **Requirements**: Any dependencies or prerequisites.  

### Branching and Commits  
- A **feature branch** will be created for each issue.  
- All commits related to an issue must start with `#<issue_number>` to link them to the corresponding issue.  

### Merge Requests and Code Review  
Once an issue meets the acceptance criteria:  
1. A **merge request (MR)** will be created.  
2. Another team member will review the Merge Request for quality, correctness, and adherence to the project standards.  
3. If approved, the branch will be merged into `main`.  

### Issue Tracking  
- **Labels** will be used to indicate the current status of each issue.  
- An **issue template** has been made that each issue need to follow to ensure consistency and clarity. This template is available in the ".gitlab" folder.
  
This workflow ensures **traceability, collaboration, and maintainability** throughout  
  
## Pipeline  
  
### CI  
The pipeline **builds and run all tests**. It will not deploy unless there is a tag.  
If a tag is done for the push the pipeline **WILL NOT** build and run tests. This is not needed for tags.  
Should a test fail the pipeline will also fail.  
  
### Docker Image  
The pipeline will only create and push a docker image if it deploys, that is a commit with a tag using semantic version.  
It does create a temporary docker image in the build-and-test stage, this is just used for to run tests inside the pipeline.   
It is only temporary and only exists in the CI-run.  

## Docker Usage
- **Build Docker image:**
  ```sh
  docker build -t template-opencv .
  ```
- **Run in Docker:**
  ```sh
  docker run template-opencv --cid=253 --name=img --width=640 --height=480
  ```
- **Docker Compose:**
  See `src/recordings/docker-compose.yaml` for integration with video replay and shared memory.

## Add your files

- [ ] [Create](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#create-a-file) or [upload](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#upload-a-file) files
- [ ] [Add files using the command line](https://docs.gitlab.com/ee/gitlab-basics/add-file.html#add-a-file-using-the-command-line) or push an existing Git repository with the following command:

```
cd existing_repo
git remote add origin https://git.chalmers.se/courses/dit638/students/2025-group-14.git
git branch -M main
git push -uf origin main
```

---

## Data Analysis & Evaluation
- **Log Formatting:**
  - `src/Data/formatting.py` extracts and formats log data for analysis.
- **Steering Evaluation:**
  - `src/Data/evaluate_steering.py` computes the percentage of predicted steering angles within a threshold of ground truth.
- **CSV and Plotting:**
  - Use the provided CSVs and Gnuplot script (`plot_rec1.gnu`) to visualize results.

---

## Project Structure
- `src/`
  - `template-opencv.cpp`: Main application (cone detection, steering, OpenDLV integration)
  - `algorithm/`: Steering angle calculation and related scripts
  - `ConeDetector/`: Cone detection logic
  - `Data/`: Python scripts and logs for data analysis
  - `recordings/`: Example `.rec` files and Docker Compose for integration
- `CMakeLists.txt`: Build configuration
- `Dockerfile`: Container build setup
- `README.md`: Project documentation

---

## Development Workflow
- **Issue Creation:**
  - Create an issue for each new feature or fix, with purpose, acceptance criteria, and requirements.
- **Branching:**
  - Use feature branches for each issue.
  - Prefix commits with `#<issue_number>`.
- **Merge Requests:**
  - Submit Merge requests for review and merge into `main` after approval.
- **CI/CD:**
  - Pipeline builds and tests all code. Docker images are built and pushed on tagged releases.

---

## Authors & Acknowledgments
- Lilly Heier
- Daniel Norberg
- Erik Gabrielsson
- Johannes Borg

Special thanks to Christian Berger, our teacher at University.

---

## License
Check Licencse file
