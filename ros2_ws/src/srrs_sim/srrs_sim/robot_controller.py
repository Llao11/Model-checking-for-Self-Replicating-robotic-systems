import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray,Empty
import math
# from ros_ign_interfaces.srv import SpawnEntity, DeleteEntity
from std_srvs.srv import Trigger
# from gz_msgs.srv import CreateJoint, RemoveJoint


class RobotController(Node):
    def __init__(self):
        super().__init__('robot_controller')

        # Publishers for attach and detach topics
        self.attach_publisher_voxel = self.create_publisher(Empty, '/attach_link_voxel', 10)
        self.detach_publisher_voxel = self.create_publisher(Empty, '/detach_link_voxel', 10)
        self.attach_publisher1 = self.create_publisher(Empty, '/attach_link1', 10)
        self.detach_publisher1 = self.create_publisher(Empty, '/detach_link1', 10)
        self.attach_publisher2 = self.create_publisher(Empty, '/attach_link2', 10)
        self.detach_publisher2 = self.create_publisher(Empty, '/detach_link2', 10)

        # Separate publishers for each joint controller
        self.command_publisher1 = self.create_publisher(Float64MultiArray,'/position_controller1/commands',10)
        self.command_publisher2 = self.create_publisher(Float64MultiArray,'/position_controller2/commands',10)
        self.command_publisher3 = self.create_publisher(Float64MultiArray,'/position_controller3/commands',10)
        self.command_publisher4 = self.create_publisher(Float64MultiArray,'/position_controller4/commands',10)
        self.command_publisher5 = self.create_publisher(Float64MultiArray,'/position_controller5/commands',10)
        self.command_publishers = [self.command_publisher1,self.command_publisher2,self.command_publisher3,
                                   self.command_publisher4,self.command_publisher5]
                                   

        # Timer to periodically send commands
        self.timer_period = 4  # seconds
        self.timer = self.create_timer(self.timer_period, self.timer_callback)
        

        # self.command_sequences_detachable = [
        #     ["a",   "",    "d",     "",     "a",     "",     ""],  # block_0
        #     ["d",   "",    "a",     "",     "d",     "",     ""],  # block_10
        # ]

        self.command_sequences_detachable = [   
            # block_0, # block_10
            ["a",   "d"], 
            ["d",   "a"],
            ["",   ""],
            ["",   ""],

            ["a",   "d"],
            ["",   ""],
            ["",   ""],
        ]
        # Separate command sequences for each joint
        self.command_sequences_deg = [
            # [0.0,  0.0,    0.0,    0.0,    0.0], 
            [0,     30,     120,    30,     0],
            [0,     60,     120,    0,     0], 
            [180,   60,     120,    0,     180], 
            [180,   30,     120,    30,    180],
            
            [180,   0,     120,    60,      180], 
            [0,     0,     120,    60,     0],
            [0,     30,     120,    30,     0], 
            # [180,   0,     120,    30,     180], 
            # [0.0,  0.0,    0.0,    0.0,    0.0]
            ]
        self.command_sequences = [[element * math.pi/180.0 for element in sublist] for sublist in self.command_sequences_deg]
        self.step = 0

        # self.detach()
        self.get_logger().info("RobotController node has been started.")


    def timer_callback(self):
        print(f"Step: {self.step}")
        if self.command_sequences_detachable[self.step][0] == "a":
            self.attach1()
        elif self.command_sequences_detachable[self.step][0] == "d":
            self.detach1()
        
        if self.command_sequences_detachable[self.step][1] == "a":
            self.attach2()
        elif self.command_sequences_detachable[self.step][1] == "d":
            self.detach2()

        # Publish commands for each joint separately
        for joint_index in range(len(self.command_sequences[0])):
            command = Float64MultiArray()
            command.data = [self.command_sequences[self.step][joint_index]]
            # command.data = [self.command_sequences[joint_index][self.step[joint_index]]]
            
            # Publish to respective joint controller
            self.command_publishers[joint_index].publish(command)

            self.get_logger().info(f"Published command for joint {joint_index+1}: {command.data}")

            # Update index for the next command
        self.step += 1
        if self.step >= len(self.command_sequences):
            self.step = 0  # Loop back to the beginning
            self.get_logger().info(f"Repeat sequence")


    def attach(self):
        msg = Empty()
        self.attach_publisher_voxel.publish(msg)
        self.get_logger().info("Published attach message.")

    def detach(self):
        msg = Empty()
        self.detach_publisher_voxel.publish(msg)
        self.get_logger().info("Published detach message.")

    def attach1(self):
        msg = Empty()
        self.attach_publisher1.publish(msg)
        self.get_logger().info("Published attach1 message.")

    def detach1(self):
        msg = Empty()
        self.detach_publisher1.publish(msg)
        self.get_logger().info("Published detach1 message.")

    def attach2(self):
        msg = Empty()
        self.attach_publisher2.publish(msg)
        self.get_logger().info("Published attach2 message.")

    def detach2(self):
        msg = Empty()
        self.detach_publisher2.publish(msg)
        self.get_logger().info("Published detach2 message.")


def main(args=None):
    rclpy.init(args=args)
    controller_node = RobotController()

    try:
        rclpy.spin(controller_node)
    except KeyboardInterrupt:
        controller_node.get_logger().info("Shutting down RobotController node...")
    finally:
        controller_node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()