#/bin/sh -e

for x in $(find ${builddir}/docs/reference/html/ -name "*.html")
do
  # echo Validating $x
  xmllint --noout $x || exit 1
done
