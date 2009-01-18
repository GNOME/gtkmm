;;
;;  french.nsh
;;
;;  French language strings for the Windows gtkmm NSIS installer.
;;  Windows Code page: 1252
;;
;;  Author: Eric Boumaour <zongo@nekeme.net>, 2003.
;;

LangString MISC_ADMIN_REQUIRED          ${LANG_FRENCH} \
  "Des droits administrateur sont nécessaires pour désinstaller${PRODUCT_NAME}. L'installation va s'arrêter maintenant..."
LangString MISC_INSTALL_OPTION          ${LANG_FRENCH} "Option d'installation"
LangString MISC_UNINSTALL_CONTEXT       ${LANG_FRENCH} \
  "${PRODUCT_NAME} peut être installé pour tous les utilisateurs ou uniquement l'utilisateur actuel."
LangString MISC_ANSWER_SYSTEM           ${LANG_FRENCH} \
  "Veuillez répondre aux questions suivantes relatives à votre système."


LangString GTKMM_PREVIOUS_VERSION       ${LANG_FRENCH} \
"Une version précédente de ${PRODUCT_NAME} ($R1) a été détectée. Etes-vous d'accord de la désinstaller maintenant ? $\n$\nCliquer sur `Oui` pour supprimer \
  la version précédente, `Non` pour l'écraser, ou `Annuler` pour annuler cette mise à jour."
LangString GTKMM_PREVIOUS_ERROR         ${LANG_FRENCH} \
  "Une erreur s'est produite ou une version précédente de ${PRODUCT_NAME} ($R1) n'a pas été correctement désinstallée. \
   L'installation va s'arrêter maintenant."
LangString GTKMM_NEWER                  ${LANG_FRENCH} \
"${PRODUCT_NAME} ($R1) est déjà installé sur votre système, et est plus récent que cette distribution (${PRODUCT_VERSION}-${PRODUCT_VERSION_INSTALLER})."
   
LangString GTKMM_ADD_PATH               ${LANG_FRENCH} \
"Ajouter le repertoire racine de gtkmm à la variable PATH"

LangString GTKMM_RIGHTS_INSTALL         ${LANG_FRENCH} \
"Installer pour"
LangString GTKMM_RIGHTS_ANYONE          ${LANG_FRENCH} \
"Tous les utilisateurs de cet ordinateur"
LangString GTKMM_RIGHTS_CURRENT         ${LANG_FRENCH} \
"Uniquement l'utilisateur actuel"
