;;
;;  simpchinese.nsh
;;
;;  Simplified Chinese language strings for the Windows gtkmm NSIS installer.
;;  Windows Code page: 936
;;
;;  Author: Tao Wang <dancefire@gmail.com>, 2009
;;

LangString MISC_ADMIN_REQUIRED          ${LANG_SIMPCHINESE} \
  "需要管理员权限来卸载 ${PRODUCT_NAME}. 现在正在退出安装软件..."
LangString MISC_INSTALL_OPTION          ${LANG_SIMPCHINESE} "安装选项"
LangString MISC_UNINSTALL_CONTEXT       ${LANG_SIMPCHINESE} \
  "您可以选择为所有这台计算机的用户或只是您自己来安装 ${PRODUCT_NAME}。"
LangString MISC_ANSWER_SYSTEM           ${LANG_SIMPCHINESE} \
  "请回答下列系统相关的问题。"

LangString GTKMM_PREVIOUS_VERSION       ${LANG_SIMPCHINESE} \
"检测到了早期版本 ${PRODUCT_NAME} ($R1). 您想现在卸载它么？ \
$\n$\n想卸载早期版本请点击 '是'，想将其覆盖请点击 '否'，想取消这次升级请点击 '取消'。"
LangString GTKMM_PREVIOUS_ERROR         ${LANG_SIMPCHINESE} \
'发生了一个位置错误，或者早期版本 ${PRODUCT_NAME} ($R1) 未能卸载。安装软件正在停止。'
LangString GTKMM_ADD_PATH               ${LANG_SIMPCHINESE} \
"添加 gtkmm 运行目录至 PATH 环境变量"
LangString GTKMM_NEWER                  ${LANG_SIMPCHINESE} \
"${PRODUCT_NAME} ($R1) 已经在您的系统上安装了，并且新于本发布版本(${PRODUCT_VERSION}-${PRODUCT_VERSION_INSTALLER})."

;; TODO: This needs to be translated!
LangString GTKMM_DIRECTORYPAGE_HINT     ${LANG_SIMPCHINESE} \
"Setup will install ${PRODUCT_FULLNAME} ${PRODUCT_VERSION} in the following folder. To install in a different folder, click Browse and select another folder. Click Next to continue.$\r$\n$\r$\nIf you intend to use MinGW, then it is not recommended to use a path that has space characters in it because this will break pkg-config."

LangString GTKMM_RIGHTS_INSTALL               ${LANG_SIMPCHINESE} \
"安装于"
LangString GTKMM_RIGHTS_ANYONE               ${LANG_SIMPCHINESE} \
"这台计算机上的所有用户"
LangString GTKMM_RIGHTS_CURRENT               ${LANG_SIMPCHINESE} \
"只有我"
