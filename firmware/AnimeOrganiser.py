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


if args.LQ and args.HQ:
    print("You can't choose both versions!")
elif args.LQ:
    os.system("AnimeOrganiserLQ \"{}\"".format(args.d))
else:
    os.system("AnimeOrganiserHQ \"{}\"".format(args.d))