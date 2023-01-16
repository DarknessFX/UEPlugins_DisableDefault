///
/// Created by DarknessFX - https://dfx.lv - @DrkFX
/// Source Code at https://github.com/DarknessFX/UEPlugins_DisableDefault
///

#include <windows.h>
#include "AppForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;
                                                                                                                                                                                                                                                                                                                                                        using namespace Microsoft::Win32;
using namespace UEPluginsDisableDefault;

void AppForm::AppForm_Load ( System::Object^ sender, System::EventArgs^ e )
{
    StateUpdate(AppState::Wait);
    cmbUEFolder->Items->Clear();
    dtbPlugins->Clear();

    StatusUpdate("Finding default Unreal Engine folder in Registry.");
    String^ UEDefaultPath = Registry::ClassesRoot->OpenSubKey("Unreal.ProjectFile\\shell\\open\\command")->GetValue("")->ToString();

    StatusUpdate("Reading Unreal Engine folder path in Registry \\\\HKEY_LOCAL_MACHINE\\SOFTWARE\\EpicGames\\Unreal Engine");
    RegistryKey^ UEKey = Registry::LocalMachine->OpenSubKey("SOFTWARE\\EpicGames\\Unreal Engine");

    for each (String^ SubKey in UEKey->GetSubKeyNames())
    {
        RegistryKey^ BuildKey = UEKey->OpenSubKey(SubKey);
        String^ UEPath = BuildKey->GetValue("InstalledDirectory")->ToString();
        cmbUEFolder->Items->Add(UEPath); 
        if ( UEDefaultPath->Contains(UEPath) ) 
        {
            cmbUEFolder->SelectedIndex = cmbUEFolder->Items->Count - 1;
        }
    }

    StatusUpdate("");
    UpdateFlow();
    StateUpdate(AppState::Default);
}    

void AppForm::AppForm_SizeChanged ( System::Object^ sender, System::EventArgs^ e )
{
    UpdateFlow();
}

void AppForm::UpdateFlow ( )
{
    cmbUEFolder->Width = AppForm::ClientSize.Width - btnBrowse->Width - lblUEFolder->Width - txtSearch->Width - 28;
}

void AppForm::StatusUpdate(String^ Message) 
{
    AppForm::lblStatus->Text = Message;
}

void AppForm::mnuShowAll_Click ( System::Object^ sender, System::EventArgs^ e )
{
    if (mnuShowDefault->Checked) 
    {
        mnuShowDefault->Checked = false;
    }
    btnMenu->Text = mnuShowAll->Text;

    for ( int iRow = 0; iRow < AppForm::grdPlugins->Rows->Count; iRow++ )
    {
        AppForm::grdPlugins->Rows[iRow]->Visible = true;
    }
}

void AppForm::mnuShowDefault_Click ( System::Object^ sender, System::EventArgs^ e )
{
    if (mnuShowAll->Checked) 
    {
        mnuShowAll->Checked = false;
    }
    btnMenu->Text = mnuShowDefault->Text;

    for ( int iRow = 0; iRow < AppForm::grdPlugins->Rows->Count; iRow++ )
    {
        if ((bool)AppForm::grdPlugins->Rows[iRow]->Cells[0]->Value != true) 
        {
            AppForm::grdPlugins->Rows[iRow]->Visible = false;
        }
    }
}

void AppForm::cmbUEFolder_SelectedIndexChanged ( System::Object^ sender, System::EventArgs^ e )
{
    Searching(cmbUEFolder->SelectedItem->ToString());
}

void AppForm::btnBrowse_Click ( System::Object^ sender, System::EventArgs^ e )
{
    ::DialogResult result = dlgBrowse->ShowDialog();
    if( result == ::DialogResult::OK )
    {
        if ( !cmbUEFolder->Items->Contains(dlgBrowse->SelectedPath) ) 
        {
            StatusUpdate(Append("Adding UE Folder Path: ", dlgBrowse->SelectedPath));
            cmbUEFolder->Items->Add(dlgBrowse->SelectedPath);
            cmbUEFolder->SelectedIndex = cmbUEFolder->Items->Count - 1;
        }
        else
        {
            StatusUpdate(Append("Path already added : ", dlgBrowse->SelectedPath));
        }
    }
}

void AppForm::btnMinimal_Click ( System::Object^ sender, System::EventArgs^ e ) 
{
    array<String^>^ aMinimal = {"AISupport", "ContentBrowserAssetDataSource", "ContentBrowserClassDataSource", "CurveEditorTools", "TextureFormateOodle", "OodleData", "PluginBrowser", "PluginUtils", "PropertyAccessEditor"};
    for ( int iRow = 0; iRow < AppForm::dtbPlugins->Rows->Count; iRow++ )
    {
        DataRow^ mDR = AppForm::dtbPlugins->Rows[iRow];
        mDR["celEnabledByDefault"] = false;
        for each (String^ sPlugin in aMinimal) 
        {
            if (mDR["celName"]->ToString()->ToLower() == sPlugin->ToLower() )
            {
                mDR["celEnabledByDefault"] = true;
                break;
            }
        }
    }
}

void AppForm::btnSave_Click ( System::Object^ sender, System::EventArgs^ e )
{
    StateUpdate(AppState::Wait);
    AppForm::txtSearch->Text = "";
    AppForm::dtbPlugins->DefaultView->RowFilter = "";
    AppForm::StatusUpdate("Saving .uplugin changes...");
    ControlsStateChange(ControlsState::Wait);

    String^ dirPlugin = Append(cmbUEFolder->SelectedItem->ToString(), "\\Engine\\Plugins\\");
    String^ filePlugin = "";

    int iMod = 0;
    for each (DataRow^ mDRPlug in dtbPlugins->Rows)
    {
        for each (DataRow^ mDROrig in dtbPluginsOrig->Rows)
        {
            if (mDRPlug["celName"] == mDROrig["celName"])
            {
                if ((bool)mDRPlug["celEnabledByDefault"] != (bool)mDROrig["celEnabledByDefault"]) 
                {
                    filePlugin = Append(dirPlugin, mDRPlug["celPath"]->ToString());
                    File::Move(filePlugin, Append(filePlugin, "_UEPlugins_DisableDefault"));
                    Application::DoEvents();

                    FileStream^ origStream = gcnew FileStream(Append(filePlugin, "_UEPlugins_DisableDefault"), FileMode::Open);
                    StreamReader^ origReader = gcnew StreamReader(origStream);

                    FileStream^ newStream = gcnew FileStream(filePlugin, FileMode::CreateNew);
                    StreamWriter^ newWriter = gcnew StreamWriter(newStream);

                    bool bMissingLine = !origReader->ReadToEnd()->Contains("EnabledByDefault");
                    origReader->DiscardBufferedData();
                    origReader->BaseStream->Seek(0, SeekOrigin::Begin);
                    while ( !origReader->EndOfStream )
                    {
                        String^ line = origReader->ReadLine();
                        if ( line->Contains("EnabledByDefault") ) 
                        {
                            line = line->Replace(mDROrig["celEnabledByDefault"]->ToString()->ToLower(), mDRPlug["celEnabledByDefault"]->ToString()->ToLower());
                        }
                        if ( bMissingLine && line->Contains("Modules") )
                        {
                          String^ InsertLine; 
                          InsertLine = "\"EnabledByDefault\": ";
                          InsertLine = InsertLine->Insert(InsertLine->Length, mDRPlug["celEnabledByDefault"]->ToString()->ToLower());
                          InsertLine = InsertLine->Insert(InsertLine->Length, ",\n");
                          InsertLine = InsertLine->Insert(InsertLine->Length, line);
                          line = InsertLine;
                          bMissingLine = false;
                        }
                        newWriter->WriteLine(line);
                    }

                    origStream->Close();
                    origStream->Close();
                    newWriter->Close();
                    newStream->Close();
                    File::Delete(Append(filePlugin, "_UEPlugins_DisableDefault"));

                    iMod++;
                    mDROrig->Delete();
                    dtbPluginsOrig->AcceptChanges();
                }
                break;
            }
        }
    }

    dtbPluginsOrig = dtbPlugins->Copy();

    ControlsStateChange(ControlsState::Default);
    StatusUpdate(Append(iMod.ToString(), " plugins changed."));
    StateUpdate(AppState::Default);
}

void AppForm::grdPlugins_CurrentCellDirtyStateChanged ( System::Object^ sender, System::EventArgs^ e )
{
    if ( grdPlugins->IsCurrentCellDirty ) 
    {
        grdPlugins->CommitEdit(DataGridViewDataErrorContexts::Commit);
        grdPlugins->EndEdit();
        dtbPlugins->AcceptChanges();
    }
}

void StateUpdate(AppState State)
{
    switch ( State ) {
        case AppState::Default:
            Application::UseWaitCursor = false;
            break;
        case AppState::Wait:
            Application::UseWaitCursor = true;
            break;
    }
}

String^ Append(String^ str0, String^ str1) 
{
    return str0->Insert(str0->Length, str1);
}

String^ ReplaceSlashes(String^ Path) 
{
    Path = Path->Replace("\\\\", "\\");
    Path = Path->Replace("\\", "/");
    return Path;
}

void Searching(String^ Path)
{
    StateUpdate(AppState::Wait);
    AppForm::StatusUpdate("Searching UPlugins ...");
    ControlsStateChange(ControlsState::Wait);
    AppForm::dtbPlugins->Clear();
    AppForm::dtbPluginsOrig->Clear();
    AppForm::grdPlugins->DataSource = nullptr;

    if ( !Path->Contains("Plugins") )
    {
        Path = Append(Path, "\\Engine\\Plugins");
    }

    //for each (String^ dirCategory in Directory::EnumerateDirectories(Path) )
    //{
        FindUPlugin(Path);
    //}

    AppForm::dtbPlugins->DefaultView->Sort = "celEnabledByDefault DESC, celFriendlyName ASC, celCategory ASC";
    AppForm::dtbPlugins->AcceptChanges();
    AppForm::dtbPluginsOrig = AppForm::dtbPlugins->Copy();
    AppForm::dtbPluginsOrig->DefaultView->Sort = "celEnabledByDefault DESC, celFriendlyName ASC, celCategory ASC";
    AppForm::grdPlugins->DataSource = AppForm::dtbPlugins;
    AppForm::grdPlugins->CurrentCell = AppForm::grdPlugins[0,0];

    ControlsStateChange(ControlsState::Default);
    AppForm::StatusUpdate(Append(Append(Append(CountEnabledByDefault().ToString(), " plugins Enabled By Default. " ), AppForm::dtbPlugins->Rows->Count.ToString()), " plugins total."));
    StateUpdate(AppState::Default);
}

void FindUPlugin(String^ Path)
{
    for each (String^ dirPlugin in Directory::EnumerateDirectories(Path) )
    {
        if ( IsIgnoredFolder(dirPlugin) ) 
        {
            continue;
        }

        AppForm::StatusUpdate(Append("Searching UPlugins :", dirPlugin));
        Application::DoEvents();

        for each (String^ mFile in Directory::GetFiles( dirPlugin, "*.uplugin" ) )
        {
            AddUPlugin(mFile);
            break;
        }
        if ( Directory::GetDirectories(dirPlugin)->Length != 0 )
        {
            FindUPlugin(dirPlugin);
        }
    }
}

void AddUPlugin(String^ FileUPlugin)
{
    DataRow^ mDR = AppForm::dtbPlugins->NewRow();
    ReadUPlugin(FileUPlugin, mDR);
    AppForm::dtbPlugins->Rows->Add(mDR);
}

void ReadUPlugin(String^ FileUPlugin, DataRow^& mDataRow)
{
    FileStream^ filestream = gcnew FileStream(FileUPlugin, FileMode::Open);
    StreamReader^ reader = gcnew StreamReader(filestream);

    mDataRow["celName"] = Path::GetFileNameWithoutExtension(FileUPlugin);
    mDataRow["celPath"] = FileUPlugin->Substring(FileUPlugin->IndexOf("plugins", StringComparison::CurrentCultureIgnoreCase) + 8);

    if ( File::Exists(Append(Path::GetDirectoryName(FileUPlugin), "\\Resources\\icon128.png")) ) 
    {
        mDataRow["celIcon"] = Drawing::Image::FromFile( Append(Path::GetDirectoryName(FileUPlugin), "\\Resources\\icon128.png") );
    }
    else
    {
        mDataRow["celIcon"] = Drawing::Image::FromFile( Append(AppForm::cmbUEFolder->SelectedItem->ToString(), "\\Engine\\Plugins\\Editor\\PluginBrowser\\Resources\\DefaultIcon128.png") );
    }

    while ( !reader->EndOfStream )
    {
        String^ line = reader->ReadLine();
        if ( line->Contains("VersionName") ) 
        {
            GetJSONValue(line);
            mDataRow["celVersionName"] = line;
            continue;            
        }
        if (line->Contains("Installed"))
        {
          GetJSONValue(line);
          mDataRow["celInstalled"] = line;
          continue;
        }
        if ( line->Contains("EnabledByDefault") ) 
        {
            GetJSONValue(line);
            mDataRow["celEnabledByDefault"] = line;
            continue;            
        }
        if ( line->Contains("FriendlyName") ) 
        {
            GetJSONValue(line);
            mDataRow["celFriendlyName"] = line;
            continue;            
        }
        if ( line->Contains("Description") ) 
        {
            GetJSONValue(line);
            mDataRow["celDescription"] = line;
            continue;            
        }
        if ( line->Contains("Category") ) 
        {
            GetJSONValue(line);
            mDataRow["celCategory"] = line;
            continue;            
        }
    }
    reader->Close();
    filestream->Close();
};

void GetJSONValue(String^& str0)
{
    if ( str0->Contains(": \"") )
    {
        str0 = str0->Substring(str0->IndexOf(": \"") + 3);
        str0 = str0->Substring(0, str0->Length - 2);
    } 
    else 
    {
        str0 = str0->Substring(str0->IndexOf(": ") + 2);
        if (str0->Substring(str0->Length - 1, 1) == ",") {
          str0 = str0->Substring(0, str0->Length - 1);
        }
        else
        {
          str0 = str0->Substring(0, str0->Length);
        }
    }
}

int CountEnabledByDefault() 
{
    int iCounted = 0;
    for each ( DataRow^ mDR in AppForm::dtbPlugins->Rows )
    {
        if ((bool)mDR["celEnabledByDefault"] == true) 
        {
            iCounted++;
        }
    }
    return iCounted;
}

bool IsIgnoredFolder(String^ Path)
{
    bool bIsIgnoreFolder = false;
    array<String^>^ aIgnoreFolders = {"Binaries", "Config", "Content", "Docs", "Intermediate", "Library", "Private", "Public", "Resources", "SDK", "SDKs", "Shaders", "Source", "SourceArt", "ThirdParty"};
    for each (String^ sIgnoreFolder in aIgnoreFolders) 
    {
        if (sIgnoreFolder->ToLower() == Path->Substring(System::IO::Path::GetDirectoryName(Path)->Length + 1)->ToLower() ) 
        {
            bIsIgnoreFolder = true;
            break;
        }
    }
    return bIsIgnoreFolder;
}

void ControlsStateChange(ControlsState State)
{
    bool bState = (bool)State;
    AppForm::cmbUEFolder->Enabled = bState;
    AppForm::btnBrowse->Enabled = bState;
    AppForm::btnMenu->Enabled = bState;
    AppForm::btnMinimal->Enabled = bState;
    AppForm::btnSave->Enabled = bState;
    AppForm::grdPlugins->Enabled = bState;
  
    switch ( bState ) {
        case false:
            AppForm::btnSave->BackColor = Color::Empty;
            break;
        case true:
            AppForm::btnSave->BackColor = Color::LightGreen;
           break;
    }
}

void AppForm::txtSearch_GotFocus(System::Object^ sender, System::EventArgs^ e)
{
  txtSearch->SelectAll();
}

void AppForm::txtSearch_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
  AppForm::dtbPlugins->DefaultView->RowFilter = String::Format("celFriendlyName LIKE '%{0}%'", txtSearch->Text);
}
