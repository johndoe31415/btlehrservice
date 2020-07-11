import argparse
parser = argparse.ArgumentParser(prog = "btlehrservice", description = "Bluetooth Low Energy Heart Rate service.", add_help = False)
parser.add_argument("-r", "--random-btle-address", action = "store_true", help = "Use a random BTLE address. Some heartrate monitors (e.g., Polar H9) seem to require this.")
parser.add_argument("-u", "--user", metavar = "username", type = str, help = "Change the username of the unix_socket to this user after it has been bound.")
parser.add_argument("-c", "--chown", metavar = "oct_permissions", type = str, help = "Change permissions of the unix_socket to this octal permission value after it has been bound.")
parser.add_argument("-v", "--verbose", action = "count", default = 0, help = "Increase verbosity. Can be specified multiple times.")
parser.add_argument("destination_address", metavar = "dest_mac_address", type = str, help = "BTLE MAC address of the device that the btlehrservice should try to connect to.")
parser.add_argument("unix_socket", metavar = "socket", type = str, help = "UNIX socket that the btlehrservice listens on.")
