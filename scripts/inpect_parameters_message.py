from rosbag import Bag


if __name__ == "__main__":
    bag_file = '/home/qbot/dynamic_recon_x86_debug.bag'
    bag = Bag(bag_file, 'r')

    msgs = []
    msgs_serialised = []
    for topic, msg, timestamp in bag.read_messages(topics=['/test_broken_node/parameter_descriptions'], raw=True):
        msgs_serialised.append(msg)

    for topic, msg, timestamp in bag.read_messages(topics=['/test_broken_node/parameter_descriptions']):
        msgs.append(msg)

    pass
