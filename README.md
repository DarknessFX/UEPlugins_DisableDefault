     .----------------.  .----------------.  .----------------. 
    | .--------------. || .--------------. || .--------------. |
    | |  ________    | || |  _________   | || |  ____  ____  | |
    | | |_   ___ `.  | || | |_   ___  |  | || | |_  _||_  _| | |
    | |   | |   `. \ | || |   | |_  \_|  | || |   \ \  / /   | |
    | |   | |    | | | || |   |  _|      | || |    > `' <    | |
    | |  _| |___.' / | || |  _| |_       | || |  _/ /'`\ \_  | |
    | | |________.'  | || | |_____|      | || | |____||____| | |
    | |              | || |              | || |              | |
    | '--------------' || '--------------' || '--------------' |
     '----------------'  '----------------'  '----------------' 

           DarknessFX @ https://dfx.lv | Twitter: @DrkFX

# UEPlugins_DisableDefault

Tool for manage Unreal Engine Plugins (.uplugins) set to Enabled By Default .<br/>

<img src="https://raw.githubusercontent.com/DarknessFX/UEPlugins_DisableDefault/main/.git_img/screenshot.jpg" width="640px" />

Unreal Engine have around 100+ plugins enabled by default. To disable one of those plugins you need to look for the respective .uplugin file and change the property *"EnabledByDefault": true* to *false*, this tool is made to easier manage this setting.<br/><br/>

Project info/blog at <a href="https://dfx.lv/UEPlugins_DisableDefault" target="_blank">https://dfx.lv/UEPlugins_DisableDefault</a> .<br/><br/>

## About

When you install (or build) Unreal Engine in your computer, it comes with a almost 500 plugins ( **UEFolder\Engine\Plugins** ). Plugins expand Unreal Engine features to include VR, AR, ArchViz, VirtualProduction, Mobile, Import/Export formats, Movie and Audio codecs, Python and more, you can enable or disable plugins per project when you need these features and you can also install more plugins from open source or Unreal Marketplace.

Around *140+ plugins are always enabled* (**EnabledByDefault**) in UE5, to verify you can create a NewProject, go to Tools > Plugins > Settings > Show Only Enabled.

<img src="https://raw.githubusercontent.com/DarknessFX/UEPlugins_DisableDefault/main/.git_img/screenshot_02.png" width="640px" />

You can manually disable plugins using the Plugin Browser but because they're **EnabledByDefault** everytime you create a new project you need to disable again, some common plugins that you maybe want to keep always disabled are ArchViz Character, Apple/Mac/iOS, Linux, Android, Hololens, MagicLeap, Steam and Oculus VR, AR, AudioCapture, IDE integration.

In UE4 some plugins like SteamVR display a warning popup (Your HDM is disconnected) eveytime you open a project and it was annoying ( like described in this <a href="https://forums.unrealengine.com/t/please-dont-launch-steamvr-with-the-editor-every-time-it-was-already-annoying-in-ue4/231420" target="_blank">thread</a> ).

The only way to change plugins **EnabledByDefault** is to manually change the .uplugin file descriptor for every plugin you want to disable, **UEFolder\Engine\Plugins** have 18.000+ subfolders, you can spend some time searching to find where the .uplugin you want to disable is located. And later when you update your UE version, all your changes are wasted because the update overwrite .uplugins to default again.

Because this changes are made in the Engine\Plugins, there are other benefits in changing .uplugins settings because this changes only affect your Engine installation,  for example you can **EnabledByDefault** plugins that you want always enabled, like RenderDoc, DFoundryFX, ElectronicNodes and this changes won't affect the .uproject file and is invisible to other devs that share the same .uproject.

*UEPlugins_DisableDefault* tool provides a better way to manage **EnabledByDefault** settings of Unreal Engine plugins.

## Credits

Icon: DefaultIcon128.png from Unreal Engine by Epic Games. <br/>
Icon: Microsoft FluentUI System Icons - https://github.com/microsoft/fluentui-system-icons <br/>
Font : Roboto-Regular by Christian Robertson - https://fonts.google.com/specimen/Roboto <br/>

## License

@MIT - Free for everyone and any use. <br/><br/>
DarknessFX @ <a href="https://dfx.lv" target="_blank">https://dfx.lv</a> | Twitter: <a href="https://twitter.com/DrkFX" target="_blank">@DrkFX</a> <br/>https://github.com/DarknessFX/UEPlugins_DisableDefault
