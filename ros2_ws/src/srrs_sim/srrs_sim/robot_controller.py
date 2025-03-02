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
        self.attach_publisher = self.create_publisher(Empty, 'attach_link', 10)
        self.detach_publisher = self.create_publisher(Empty, 'detach_link', 10)

        # Separate publishers for each joint controller
        self.command_publisher1 = self.create_publisher(Float64MultiArray,'/position_controller1/commands',10)
        self.command_publisher2 = self.create_publisher(Float64MultiArray,'/position_controller2/commands',10)
        self.command_publisher3 = self.create_publisher(Float64MultiArray,'/position_controller3/commands',10)
        self.command_publisher4 = self.create_publisher(Float64MultiArray,'/position_controller4/commands',10)
        self.command_publisher5 = self.create_publisher(Float64MultiArray,'/position_controller5/commands',10)
        self.command_publishers = [self.command_publisher1,self.command_publisher2,self.command_publisher3,
                                   self.command_publisher4,self.command_publisher5]
                                   

        # Timer to periodically send commands
        self.timer_period = 3  # seconds
        self.timer = self.create_timer(self.timer_period, self.timer_callback)


        # Separate command sequences for each joint
        self.command_sequences_deg = [
            [0.0,   90,    45,    0,   -45,    -90,    0.0],  # Joint 1
            [0.0,   45,    45,    0,   -45,    -90,    0.0],  # Joint 2
            [0.0,   45,    45,    0,   -45,     -90,    0.0],  # Joint 3
            [0.0,   90,    45,    0,   -45,    -90,    0.0],  # Joint 4
            [0.0,   90,    45,    0,   -45,     -90,    0.0],  # Joint 5
        ]
        self.command_sequences = [[element * math.pi/180.0 for element in sublist] for sublist in self.command_sequences_deg]
        
        self.command_sequences
        self.command_indices = [0] * len(self.command_sequences)

        self.detach()
        self.get_logger().info("RobotController node has been started.")



        
    def timer_callback(self):
        # Publish commands for each joint separately
        for joint_index in range(len(self.command_sequences)):
            command = Float64MultiArray()
            command.data = [self.command_sequences[joint_index][self.command_indices[joint_index]]]
            
            # Publish to respective joint controller
            self.command_publishers[joint_index].publish(command)

            self.get_logger().info(f"Published command for joint {joint_index+1}: {command.data}")

            # Update index for the next command
            self.command_indices[joint_index] += 1
            if self.command_indices[joint_index] >= len(self.command_sequences[joint_index]):
                self.command_indices[joint_index] = 0  # Loop back to the beginning
                self.get_logger().info(f"Repeat sequence")
                self.attach()

    def attach(self):
        msg = Empty()
        self.attach_publisher.publish(msg)
        self.get_logger().info("Published attach message.")

    def detach(self):
        msg = Empty()
        self.detach_publisher.publish(msg)
        self.get_logger().info("Published detach message.")


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