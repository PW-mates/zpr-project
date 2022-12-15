# zpr-project

### Connect to localhost
ssh-keygen -t rsa -f test_key
cat test_key.pub >> ~/.ssh/authorized_keys
./zpr_sync --pl /. --n user@localhost --pr /Downloads/ --k pathToKey