#!/usr/bin/python3
import argparse
import os

# Call parameters
parser = argparse.ArgumentParser()
parser.add_argument("-d",  type=str, default="./",
                    help="path to download")
parser.add_argument('-HQ', action='store_true') # HQ on default
parser.add_argument('-LQ', action='store_true')
args = parser.parse_args()


path = args.d.replace("\\","")

# Get subdirs to current dir
subdirs = next(os.walk(args.d))[1]
match = []

for subdir in subdirs:
    if subdir[0] == '[':                    # start with [
        idx = subdir.find("]")              # find first ]
        if idx != -1:                       # if not foudn
            if subdir[1:idx].isnumeric():   # is number
                match.append(subdir)

if args.LQ and args.HQ:
    print("\033[31mYou can't choose both versions!\033[0m")
    exit(1)
if args.LQ:
    ver = "AnimeOrganiserLQ"
else:
    ver = "AnimeOrganiserHQ"
    
print("\033[34m") #blue
if match:
    print("Anime season folders detected!")
    print("Initializing sequence of pain and destruction...")
    for m in match:
        path = "{}/{}".format(args.d,m)
        command = "{} \"{}\"".format(ver, path)
        print("\033[36m") #blue
        print("-"*70)
        print("Executing Anime Organiser for '{}'...".format(path))
        print("-"*70)
        os.system(command)
else:
    print("\033[36m") #blue
    print("-"*70)
    print("Executing Anime Organiser for '{}'...".format(args.d))
    print("-"*70)
    command = "{} \"{}\"".format(ver, args.d)
    os.system(command)
    
    
