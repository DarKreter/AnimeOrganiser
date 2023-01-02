#!/bin/bash

# first input argument should be [if exist] path
if [ "$1" ]  
    then
    cd "$1" # if exists change dir to this folder and then execute AnimeOrganiser
fi # if no input arg, execute in current dir

# Call by full name
/home/kretes/k8d.server.anime_organiser/Execute\ Files/AnimeOrganiserLQ\ v.3 $2