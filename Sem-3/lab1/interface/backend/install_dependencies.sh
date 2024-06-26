backend_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$backend_path"

rm -rf dependencies;
mkdir dependencies

# cpp-httplib
mkdir dependencies/cpp-httplib
curl https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h --output ./dependencies/cpp-httplib/httplib.h

echo "Dependencies installed successfully!"