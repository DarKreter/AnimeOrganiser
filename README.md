**Anime Organiser** is tool that sorts and organise series with/without soft subtitles. It renames video and subtitle files with convention: `series-title - sXXeYY.{ext}`, where XX defines season number and YY defines episode number.

It's created to help you easily organise downloaded series for services like **plex** or **emby**.

**Install requirements:**
```
sudo apt update
sudo apt install $(cat requirements/apt.txt)
pip3 install -r requirements/pip.txt
```

You can
**Build project** from source:
```
mkdir build
cmake -S . -B build/
cmake --build build -t AnimeOrganiserHQ
cmake --build build -t AnimeOrganiserLQ
```
Or **use existing binaries/scripts**:

- To run directly in current dir `"./AnimeOrganiserHQ v.3"`
- Wrapper to run in any directory `./AnimeOrganiserHQ.sh [path]`
- Run with nice args handling `./AnimeOrganiser.py [-d path] [{-LQ,-HQ}]`
