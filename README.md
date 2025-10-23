# Model checking for self-replicating robotic systems

This repository is a part of the master thesis "Model checking for self-replicating robotic systems"

Structure of the project:
- **code** : stand-alone modules for local and 2D reachability analysis, robot configuration model checking and counterexample parsing of self-replicating robotic systems (SRRS).
- **ros2_ws** : ROS2 workspace for simulation and validation of SRRS model checking results
- **Thesis LaTex**: master thesis in LaTex format
- **3Dmodels** : 3D Models used for simulation

## Description

This project investigates how formal verification and model checking – can be integrated into the design and control of SRRS to provide provable guarantees of liveness,
safety, and functional correctness.

### Requirements:
- Python 3.12
- ROS2 Jazzy
- Gazebo Harmonic

## Code references in the Thesis:
- Chapter 4. Implementation of model checking in SRRS
  - 4.3 Model checking based control in local space:
    - 4.3.3: [robot_structure.smv](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/code/configuration%20checking/smv/robot_structure.smv)
    - 4.3.4: [counterexample_control.py](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/code/configuration%20checking/counterexample_control.py) run code: <code>python3.12 counterexample_control.py</code>
  - 4.4 Reachability model checking in 2D space:
    - 4.4.2: [Assemble_initial_template.smv](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/code/global_reachability/Assemble_initial_template.smv)
    - 4.4.3: [UI.py](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/code/global_reachability/UI.py) run code: <code>python3.12 UI.py</code>
      <details>
      <summary>Configuration setup:</summary>
  
      Input part types, ( one of types should be "NONE"), robot size = 6, and field size
      <img width="251" height="65" alt="image" src="https://github.com/user-attachments/assets/d28aded6-54bb-4997-a7e9-c3e471dc0086" />
  
      press button "Create field": <img width="102" height="30" alt="image" src="https://github.com/user-attachments/assets/453ca9f6-661c-40cb-94d6-36f76147f099" />
  
      On the right side choose robot structure sequence <img width="60" height="148" alt="image" src="https://github.com/user-attachments/assets/ea238bc8-87b5-419a-b023-c7990754d014" />
  
      Position parts on the field <img width="313" height="307" alt="image" src="https://github.com/user-attachments/assets/7a53e98e-e49e-41ce-81a5-2f3e4dd5ad79" />
  
      press button "Generate model: "<img width="102" height="27" alt="image" src="https://github.com/user-attachments/assets/81c0c83e-ccd2-4523-8f83-21ed69b5e278" />
  
      press button "Verify model": <img width="102" height="27" alt="image" src="https://github.com/user-attachments/assets/d6760bf9-ae98-4af2-80e1-7ff75d98d0fe" />
   
      </details>
  - 4.5 Robot configuration model checking
    - Section 4.5.2: run code: <code>python3.12 configurations_checking.py</code>
      - [Configurations_checking class](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/code/configuration%20checking/configurations_checking.py)
      - [Counterexample class](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/code/configuration%20checking/counterexample.py)
      - [Robot class](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/code/configuration%20checking/robot.py)
      - [Block class](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/code/configuration%20checking/block.py)
  - 4.6 (*change section to 4.5.3*) Aggregated configuration checking in NuSMV
    - [robot_structure_aggregated.smv](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/code/configuration%20checking/smv_aggregated/robot_structure_aggregated_point_length6.smv)
- Chapter 5. Simulation of the SRRS
  - 5.1 System Architecture:
    - [GUI class](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/ros2_ws/src/srrs_sim/srrs_sim/robot_controller_gui.py)
    - [SRRScontrollerNode](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/ros2_ws/src/srrs_sim/srrs_sim/SRRScontrollerNode.py)
    - [SensorNode](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/ros2_ws/src/srrs_sim/srrs_sim/SRRSsensorsNode.py)
    - [RobotController](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/ros2_ws/src/srrs_sim/srrs_sim/robotController.py)
    - [MaterialController](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/ros2_ws/src/srrs_sim/srrs_sim/materialController.py)
    - [PartController](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/ros2_ws/src/srrs_sim/srrs_sim/partController.py)
  - 5.2.1 [Base model.sdf](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/ros2_ws/src/srrs_sim/sdf/base.sdf)
  - 5.2.2 [Part.xacro](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/ros2_ws/src/srrs_sim/urdf/part.xacro)
  - 5.3.1 [Robot.xacro](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/ros2_ws/src/srrs_sim/urdf/robot.xacro)
  - 5.3.2 [RobotController](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/ros2_ws/src/srrs_sim/srrs_sim/robotController.py)
  - 5.4 [robot_controller_gui.py](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/ros2_ws/src/srrs_sim/srrs_sim/robot_controller_gui.py)
    <details>
      <summary>run simulation</summary>
       <code>
         cd ros2_ws
         source /opt/ros/jazzy/setup.bash
         source install/setup.bash
         ros2 launch srrs_sim robot.launch.py</code>
      </details>
- Chapter 6. Evaluation and validation
  - 6.1 Validation of the counterexample based robot control [counterexample_control.py](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/code/configuration%20checking/counterexample_control.py)

    run code: <code>python3.12 counterexample_control.py</code>
  - 6.2.1 Comparison of individual and aggregated model checking:  [validation_individual_configurations.py](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/code/configuration%20checking/validation_individual_configurations.py)
 
      run code: <code>python3.12 validation_individual_configurations.py</code>

      [validation_aggregated_configurations.py](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/code/configuration%20checking/validation_aggregated_configurations.py)

      run code: <code>python3.12 validation_aggregated_configurations.py</code>
  - 6.2.2 Simulation of eligible configurations:

      [robot_config_validation.launch.py](https://github.com/Llao11/Model-checking-for-Self-Replicating-robotic-systems/blob/main/ros2_ws/src/srrs_sim/launch/robot_config_validation.launch.py)
     <details>
      <summary>run simulation</summary>
       <code>
          cd ros2_ws
          source /opt/ros/jazzy/setup.bash
          source install/setup.bash
          ros2 launch srrs_sim robot_config_validation.launch.py</code>
      </details>
      
    
