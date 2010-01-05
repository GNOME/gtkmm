;;
;;  english.nsh
;;
;;  Default language strings for the Windows gtkmm NSIS installer.
;;  Windows Code page: 1252
;;
;;  Author: Herman Bloggs <hermanator12002@yahoo.com>
;;

LangString MISC_ADMIN_REQUIRED          ${LANG_ENGLISH} \
  "Administrator rights are required to uninstall ${PRODUCT_NAME}. Exiting the installer now..."
LangString MISC_INSTALL_OPTION          ${LANG_ENGLISH} "Install Option"
LangString MISC_UNINSTALL_CONTEXT       ${LANG_ENGLISH} \
  "You can choose to install ${PRODUCT_NAME} for anyone who uses this computer or only you."
LangString MISC_ANSWER_SYSTEM           ${LANG_ENGLISH} \
  "Please answer the following system-related questions."

LangString GTKMM_PREVIOUS_VERSION       ${LANG_ENGLISH} \
"A previous version of ${PRODUCT_NAME} ($R1) has been detected. Do you agree to uninstall it now ? \
$\n$\nClick `Yes` to remove the previous version , `No` to overwrite it, or `Cancel` to \
cancel this upgrade."
LangString GTKMM_PREVIOUS_ERROR         ${LANG_ENGLISH} \
'An error occured or a previous version of ${PRODUCT_NAME} ($R1) was not uninstalled. \
The installer will stop now.'
LangString GTKMM_ADD_PATH               ${LANG_ENGLISH} \
"Add the gtkmm runtime directory to the PATH variable"
LangString GTKMM_NEWER                  ${LANG_ENGLISH} \
"${PRODUCT_NAME} ($R1) is already installed on your system, and is newer than this distribution (${PRODUCT_VERSION}-${PRODUCT_VERSION_INSTALLER})."

LangString GTKMM_DIRECTORYPAGE_HINT     ${LANG_ENGLISH} \
"Setup will install ${PRODUCT_FULLNAME} ${PRODUCT_VERSION} in the following folder. To install in a different folder, click Browse and select another folder. Click Next to continue.$\r$\n$\r$\nIf you intend to use MinGW, then it is not recommended to use a path that has space characters in it because this will break pkg-config."

LangString GTKMM_RIGHTS_INSTALL               ${LANG_ENGLISH} \
"Install for"
LangString GTKMM_RIGHTS_ANYONE               ${LANG_ENGLISH} \
"Anyone who uses this computer"
LangString GTKMM_RIGHTS_CURRENT               ${LANG_ENGLISH} \
"Only me"
