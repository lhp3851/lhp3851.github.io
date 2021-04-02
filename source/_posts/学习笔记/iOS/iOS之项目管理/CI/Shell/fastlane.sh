#!/bin/sh

#设置xcode build超时时间
export FASTLANE_XCODEBUILD_SETTINGS_TIMEOUT=120
#双步验证
export FASTLANE_APPLE_APPLICATION_SPECIFIC_PASSWORD="****-****-****-****"

#打包并导出IPA
fastlane gym\
    --workspace ${workspace_path}\
    --configuration ${signingType}\
    --scheme ${scheme}\
    --clean true\
    --include_bitcode false\
    --include_symbols false\
    --codesigning_identity "${codesigning_identity}"\
    --output_directory ${output_path}\
    --output_name "${ipa_name}"\
    --build_path ${output_path}\
    --export_options ${export_plist_path} 


#下载metadata， 包括icon（目前用不到）和各本地化发版文案。
fastlane deliver download_metadata\
    --username ${user_name}\
    --app_identifier ${bundle_id}\
    --force true
    
#简中，繁中，发版文案路径
zhHans_notes_path="./fastlane/metadata/zh-Hans/release_notes.txt"
zhHant_notes_path ="./fastlane/metadata/zh-Hant/release_notes.txt"

if [ -n "$release_notes_zhHans" ]; then
   echo "$release_notes_zhHans" > $zhHans_notes_path
fi

if [ -n "$release_notes_zhHant" ]; then
   echo "$release_notes_zhHant" > $zhHant_notes_path
fi



#上传IPA到App Store Connect
fastlane deliver\
   --username ${user_name}\
   --app_identifier ${bundle_id}\
   --app  ${app_id}\
   --ipa ${ipa_path}\
   --skip_screenshots true\
   --skip_metadata true\
   --app_version ${app_version}\
   --force true

#向keychain中添加iTunesConnect帐号密码
fastlane fastlane-credentials add --username xxx@qq.com

#移除旧密码：
fastlane fastlane-credentials remove --username xxx@qq.com