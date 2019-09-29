import argparse
parser = argparse.ArgumentParser(prog = "btlehrservice", description = "Bluetooth Low Energy Heart Rate service.", add_help = False)
parser.add_argument("destination_address", metavar = "dest_mac_address", type = str, help = "BTLE MAC address of the device that the btlehrservice should try to connect to.")
parser.add_argument("unix_socket", metavar = "socket", type = str, help = "UNIX socket that the btlehrservice listens on.")
