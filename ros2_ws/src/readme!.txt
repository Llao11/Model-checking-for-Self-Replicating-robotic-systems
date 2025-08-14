Install:
sudo apt install ros-jazzy-cv-bridge

TODO:

Начать писать спецификацию сверху-вниз (от абстрактной модели к НюСМВ модели)

    Узнать есть ли автоматические трансляторы РОС в НюСМВ

    Выделить часть кода которая моделирует систему управления робота и ее смоделировать в НюСМВ

Продолжить разрабатывать симуляцию

    добавить блок с захватом (фиксацией по плоскости вокселя) и контактным сенсором

Спецификации:
    Достижимость всех блоков для сборки
    No collision


Try to get feedback from the failed verification, where?, why? 
translate the result from NuSMV to the simulation. 
Represent and interpret counterexamples



SIMULATION:
ros2 launch srrs_sim robot.launch.py
ros2 run  srrs_sim robot_controller

console control:
    ros2 topic pub -1 /position_controller2/commands std_msgs/msg/Float64MultiArray "{data: [1.5]}"
    ros2 topic pub /detach_link1 std_msgs/msg/Empty "{}"
    ros2 topic pub /attach_obj_link1 std_msgs/msg/Empty "{}"

Разобраться в примерах
ros2 launch srrs_sim test.launch.py
ros2 run srrs_sim example_velocity 



Error:Failed to load system plugin [libign_ros2_control-system.so] : Could not find shared library.
sudo apt install ros-jazzy-gz-ros2-control
export GZ_SIM_SYSTEM_PLUGIN_PATH=/opt/ros/jazzy/lib/

Gazebo plugins: /opt/ros/jazzy/opt/gz_sim_vendor/lib

Error with faled position_controller is because of the base model (too slow to load it or smthg like this)

For gripping simulation:
    sudo apt install ros-jazzy-moveit  -- didnt work
    libDetachableJointPlugin


ADD SENSORS:
    Contact sensors:
        - check names in sdf:
            xacro robot.xacro > temp_robot.urdf 
            gz sdf -p temp_robot.urdf > temp_robot.sdf


Spawn object during runtime: 
    xacro $(ros2 pkg prefix --share srrs_sim)/urdf/part.xacro part_num:=42 > /tmp/part42.urdf 
    ros2 run ros_gz_sim create  -world empty  -name  part42  -file  /tmp/part42.urdf   -x 0.40 -y -0.25 -z 0.134



    <plugin filename="gz-sim-pose-publisher-system" name="gz::sim::systems::PosePublisher">
      <publish_model_pose>false</publish_model_pose>
      <publish_visual_pose>true<publish_visual_pose>
      <publish_collision_pose>true<publish_collision_pose>
      <publish_nested_model_pose>true<publish_nested_model_pose>
      <publish_link_pose>false</publish_link_pose>     <!-- set true if you also want link poses -->
      <use_pose_vector_msg>false</use_pose_vector_msg> <!-- per-entity topics, not Pose_V -->
      <update_frequency>30</update_frequency>          <!-- Hz -->
    </plugin>





TODO: Create a NuSMV model for check the different structures of a robot and a specifications for ability to reach different cells 
TODO paper: devide the background to the general overview and relevant to my work
