sudo apt update

sudo apt install $(cat requirements/apt.txt)

pip3 install -r requirements/pip.txt
