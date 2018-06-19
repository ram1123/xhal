#!/bin/sh

# default action
python setup.py install --single-version-externally-managed -O1 --root=$RPM_BUILD_ROOT --record=INSTALLED_FILES

# install 'scripts' to /opt/xhal/bin
mkdir -p %{buildroot}/opt/xhal/bin
cp -rfp xhal/scripts/*.py %{buildroot}/opt/xhal/bin/

find %{buildroot} -type f -exec chmod a+r {} \;
find %{buildroot} -type f -iname '*.cfg' -exec chmod a-x {} \;

# set permissions
cat <<EOF >>INSTALLED_FILES
%attr(0755,root,root) /opt/xhal/bin/*.py
%attr(0755,root,root) /usr/lib/python*/site-packages/xhal/scripts/*.py
EOF
echo "Modified INSTALLED_FILES"
cat INSTALLED_FILES
