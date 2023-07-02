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
    Application::EnableVisualStyles();

    StateUpdate(AppState::Wait);
    cmbUEFolder->Items->Clear();
    dtbPlugins->Clear();

    StatusUpdate("Finding default Unreal Engine folder in Registry.");
    String^ UEDefaultPath = Registry::ClassesRoot->OpenSubKey("Unreal.ProjectFile\\shell\\open\\command")->GetValue("")->ToString();

    StatusUpdate("Reading Unreal Engine folder path in Registry \\\\HKEY_LOCAL_MACHINE\\SOFTWARE\\EpicGames\\Unreal Engine");
    RegistryKey^ UEKey = Registry::LocalMachine->OpenSubKey("SOFTWARE\\EpicGames\\Unreal Engine");

    for each (String^ SubKey in UEKey->GetSubKeyNames()) {
      RegistryKey^ BuildKey = UEKey->OpenSubKey(SubKey);
      if (BuildKey->GetValue("InstalledDirectory")) {
        String^ UEPath = BuildKey->GetValue("InstalledDirectory")->ToString();
        if (Directory::Exists(UEPath)) {
          cmbUEFolder->Items->Add(UEPath);
        }
      }
    }

    if (cmbUEFolder->Items->Count != 0) {
      cmbUEFolder->SelectedIndex = cmbUEFolder->Items->Count - 1;
    }

    StatusUpdate("Finding .uplugins_backup with our backup file.");
    BackupAll();

    UpdateFlow();
    mnuTemplateMinimal->Visible = false;
    cmbUEFolder->Focus();
    StateUpdate(AppState::Default);
}    

void AppForm::AppForm_SizeChanged ( System::Object^ sender, System::EventArgs^ e )
{
    UpdateFlow();
}

void AppForm::UpdateFlow ( )
{
    cmbUEFolder->Width = ClientSize.Width - 
      mnuStrip->Width - 
      splitter1->Width - 
      btnBrowse->Width - 
      lblUEFolder->Width - 
      txtSearch->Width - 
      56;
}

void StatusUpdate(String^ Message) 
{
    AppForm::lblStatus->Text = Message;
}

void AppForm::mnuShowAll_Click ( System::Object^ sender, System::EventArgs^ e )
{
    if (mnuShowEnabled->Checked)
    {
        mnuShowEnabled->Checked = false;
    }
    mnuShowAll->Checked = true;

    for ( int iRow = 0; iRow < AppForm::grdPlugins->Rows->Count; iRow++ )
    {
        AppForm::grdPlugins->Rows[iRow]->Visible = true;
    }
}

void AppForm::mnuShowEnabled_Click ( System::Object^ sender, System::EventArgs^ e )
{
    if (mnuShowAll->Checked) 
    {
        mnuShowAll->Checked = false;
    }
    mnuShowEnabled->Checked = true;

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

void AppForm::mnuTemplateMinimal_Click ( System::Object^ sender, System::EventArgs^ e ) 
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
    StatusUpdate("Saving .uplugin changes...");
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
                if ((bool)mDRPlug["celEnabledByDefault"] != (bool)mDROrig["celEnabledByDefault"] || 
                    (bool)mDRPlug["celInstalled"] != (bool)mDROrig["celInstalled"]) 
                {
                    filePlugin = Append(dirPlugin, mDRPlug["celPath"]->ToString());
                    File::Move(filePlugin, Append(filePlugin, "_UEPlugins_DisableDefault"));
                    Application::DoEvents();

                    FileStream^ origStream = gcnew FileStream(Append(filePlugin, "_UEPlugins_DisableDefault"), FileMode::Open);
                    StreamReader^ origReader = gcnew StreamReader(origStream);

                    FileStream^ newStream = gcnew FileStream(filePlugin, FileMode::CreateNew);
                    StreamWriter^ newWriter = gcnew StreamWriter(newStream);

                    bool bMissingLineEBD = !origReader->ReadToEnd()->Contains("EnabledByDefault");
                    bool bMissingLineINS = !origReader->ReadToEnd()->Contains("Installed");

                    origReader->DiscardBufferedData();
                    origReader->BaseStream->Seek(0, SeekOrigin::Begin);
                    while ( !origReader->EndOfStream )
                    {
                        String^ line = origReader->ReadLine();
                        if ( line->Contains("EnabledByDefault") && (bool)mDRPlug["celEnabledByDefault"] != (bool)mDROrig["celEnabledByDefault"]) 
                        {
                            line = line->Replace(mDROrig["celEnabledByDefault"]->ToString()->ToLower(), mDRPlug["celEnabledByDefault"]->ToString()->ToLower());
                        }
                        if ( line->Contains("Installed") && (bool)mDRPlug["celInstalled"] != (bool)mDROrig["celInstalled"]) 
                        {
                            line = line->Replace(mDROrig["celInstalled"]->ToString()->ToLower(), mDRPlug["celInstalled"]->ToString()->ToLower());
                        }
                        if ( bMissingLineEBD && line->Contains("Modules") )
                        {
                          String^ InsertLine; 
                          InsertLine = "\"EnabledByDefault\": ";
                          InsertLine = InsertLine->Insert(InsertLine->Length, mDRPlug["celEnabledByDefault"]->ToString()->ToLower());
                          InsertLine = InsertLine->Insert(InsertLine->Length, ",\n");
                          InsertLine = InsertLine->Insert(InsertLine->Length, line);
                          line = InsertLine;
                          bMissingLineEBD = false;
                        }
                        if ( bMissingLineINS && line->Contains("Modules") )
                        {
                          String^ InsertLine; 
                          InsertLine = "\"Installed\": ";
                          InsertLine = InsertLine->Insert(InsertLine->Length, mDRPlug["celInstalled"]->ToString()->ToLower());
                          InsertLine = InsertLine->Insert(InsertLine->Length, ",\n");
                          InsertLine = InsertLine->Insert(InsertLine->Length, line);
                          line = InsertLine;
                          bMissingLineINS = false;
                        }
                        newWriter->WriteLine(line);
                    }

                    newWriter->Close();
                    newStream->Close();
                    origReader->Close();
                    origStream->Close();
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

void AppForm::grdPlugins_CellDoubleClick ( System::Object^ sender, DataGridViewCellEventArgs^ e )
{
  // Double-Click PATH column open Windows Explorer
  if (e->ColumnIndex == 7) {
    String^ PluginPath; 
    PluginPath = Append(cmbUEFolder->SelectedItem->ToString(), "\\Engine\\Plugins\\");
    PluginPath = Append(PluginPath, grdPlugins[e->ColumnIndex, e->RowIndex]->Value->ToString());
    PluginPath = PluginPath->Substring(0, PluginPath->LastIndexOf("\\"));
    System::Diagnostics::Process::Start(PluginPath);
  }
}

void AppForm::mnuShow_MouseHover(System::Object^ sender, System::EventArgs^ e)
{
  StatusUpdate("Filter list to show All plugins or only Enabled plugins.");
}

void AppForm::mnuBackup_MouseHover(System::Object^ sender, System::EventArgs^ e)
{
  StatusUpdate("Save or Load backup of plugins state.");
}

void AppForm::mnuTemplate_MouseHover(System::Object^ sender, System::EventArgs^ e)
{
  StatusUpdate("Save or Load templates of plugins state lists.");
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
    StatusUpdate("Searching UPlugins ...");
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
    StatusUpdate(Append(Append(Append(CountEnabledByDefault().ToString(), " plugins Enabled By Default. " ), AppForm::dtbPlugins->Rows->Count.ToString()), " plugins total."));
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

        StatusUpdate(Append("Searching UPlugins :", dirPlugin));
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
    }
    if (str0->Length > 0)
    {
      str0 = str0->Trim();
      if (str0->Substring(str0->Length - 1, 1) == ",") 
      {
          str0 = str0->Substring(0, str0->Length - 1);
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
    AppForm::mnuMain->Enabled = bState;
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

  if (e->Control && e->KeyCode == Keys::A) {
    if (sender != nullptr)
      ((TextBox^)sender)->SelectAll();
  }
}

void BackupAll() 
{
  String^ bkpPath = Append(Application::StartupPath, "\\UEPlugins_DisableDefault.uplugins_backup");
  if (!File::Exists(bkpPath)) {
    StateUpdate(AppState::Wait);
    StatusUpdate("Generating backup before first use...");
    ControlsStateChange(ControlsState::Wait);

    FileStream^ newStream = gcnew FileStream(bkpPath, FileMode::CreateNew);
    StreamWriter^ newWriter = gcnew StreamWriter(newStream);
    
    for each (String^ UEPath in AppForm::cmbUEFolder->Items) {
      Collections::Generic::List<String^>^ aPlugins = FindAllUPlugins(Append(UEPath, "\\Engine\\Plugins"));
      for each (String^ sPlugin in aPlugins) {
        for each(String^ sLine in File::ReadLines(sPlugin)) {
          if (sLine->Contains("EnabledByDefault") && sLine->Contains("true")) {
            newWriter->WriteLine(sPlugin);
          }
        }
      }
    }
    newWriter->Close();
    newStream->Close();
    ControlsStateChange(ControlsState::Default);
    StatusUpdate(Append("Backup created at ", bkpPath));
    StateUpdate(AppState::Default);
  } else {
    StatusUpdate("");
  }
}

List<String^>^ FindAllUPlugins(String^ Path) {
  Generic::List<String^>^ aPluginsList = gcnew Generic::List<String^>();
  for each (String ^ dirPlugin in Directory::EnumerateDirectories(Path)) {
    if (IsIgnoredFolder(dirPlugin)) {
      continue;
    }
    for each (String ^ mFile in Directory::GetFiles(dirPlugin, "*.uplugin")) {
      aPluginsList->Add(mFile);
      break;
    }
    if (Directory::GetDirectories(dirPlugin)->Length != 0) {
      Generic::List<String^>^ aPluginsSubList = FindAllUPlugins(dirPlugin);
      for each (String^ SubList in aPluginsSubList) {
        aPluginsList->Add(SubList);
      }
    }
  }
  return aPluginsList;
}

void AppForm::mnuBackupSave_Click(System::Object^ sender, System::EventArgs^ e)
{
  bool bIsTemplate = false;
  bIsTemplate = sender->ToString()->Contains("template");

  String^ bkpPath;
  if (!bIsTemplate) {
    bkpPath = Append(Application::StartupPath, "\\*.uplugins_backup");
  } else {
    bkpPath = Append(Application::StartupPath, "\\*.uplugins_template");
  }

  SaveFileDialog^ dlgBkpSave = gcnew SaveFileDialog();
  dlgBkpSave->AddExtension = true;
  dlgBkpSave->CheckPathExists = true;
  if (!bIsTemplate) {
    dlgBkpSave->FileName = "MyBackup_01";
    dlgBkpSave->DefaultExt = ".uplugins_backup";
    dlgBkpSave->Filter = "Default|*.uplugins_backup";
    dlgBkpSave->Title = "Save uplugins_backup";
  } else {
    dlgBkpSave->FileName = "MyTemplate_01";
    dlgBkpSave->DefaultExt = ".uplugins_template";
    dlgBkpSave->Filter = "Default|*.uplugins_template";
    dlgBkpSave->Title = "Save uplugins_template";
  }
  dlgBkpSave->InitialDirectory = Application::StartupPath;
  dlgBkpSave->OverwritePrompt = true;
  if (dlgBkpSave->ShowDialog() == Windows::Forms::DialogResult::OK) {
    bkpPath = dlgBkpSave->FileName;
    if (bkpPath->Contains("UEPlugins_DisableDefault.uplugins_backup")) {
      MessageBox::Show(this, 
        "Please, don't use UEPlugins_DisableDefault.uplugins_backup name, this is your main backup for all Unreal Engine folders. Try again with a different filename.", 
        "UEPlugins_DisableDefault", 
        MessageBoxButtons::OK, 
        MessageBoxIcon::Information);
      return;
    }

    StateUpdate(AppState::Wait);
    if (!bIsTemplate) {
      StatusUpdate("Saving backup...");
    } else {
      StatusUpdate("Saving template...");
    }
    ControlsStateChange(ControlsState::Wait);

    if (File::Exists(bkpPath)) File::Delete(bkpPath);
    FileStream^ newStream = gcnew FileStream(bkpPath, FileMode::CreateNew);
    StreamWriter^ newWriter = gcnew StreamWriter(newStream);
    for each (DataRow ^ mDRPlug in dtbPlugins->Rows) {
      String^ UEPath = Append(AppForm::cmbUEFolder->SelectedItem->ToString(), "\\Engine\\Plugins\\");
      if (mDRPlug["celEnabledByDefault"]->ToString()->ToLower() == "true") {
        if (!bIsTemplate) {
          newWriter->WriteLine(Append(UEPath, mDRPlug["celPath"]->ToString()));
        } else {
          newWriter->WriteLine(mDRPlug["celPath"]->ToString());
        }
      }
    }
    newWriter->Close();
    newStream->Close();

    ControlsStateChange(ControlsState::Default);
    if (!bIsTemplate) {
      StatusUpdate(Append("Backup created at ", bkpPath));
    } else {
      StatusUpdate(Append("Template created at ", bkpPath));
    }
    StateUpdate(AppState::Default);
  }
}

void AppForm::mnuBackupLoad_Click(System::Object^ sender, System::EventArgs^ e)
{
  bool bIsTemplate = false;
  bIsTemplate = sender->ToString()->Contains("template");

  String^ bkpPath;
  if (!bIsTemplate) {
    bkpPath = Append(Application::StartupPath, "\\*.uplugins_backup");
  } else {
    bkpPath = Append(Application::StartupPath, "\\*.uplugins_template");
  }

  OpenFileDialog^ dlgBkpSave = gcnew OpenFileDialog();
  dlgBkpSave->AddExtension = true;
  dlgBkpSave->CheckFileExists = true;
  dlgBkpSave->CheckPathExists = true;

  if (!bIsTemplate) {
    dlgBkpSave->FileName = "MyBackup_01";
    dlgBkpSave->DefaultExt = ".uplugins_backup";
    dlgBkpSave->Filter = "Default|*.uplugins_backup";
    dlgBkpSave->Title = "Load uplugins_backup";
  } else {
    dlgBkpSave->FileName = "MyTemplate_01";
    dlgBkpSave->DefaultExt = ".uplugins_template";
    dlgBkpSave->Filter = "Default|*.uplugins_template";
    dlgBkpSave->Title = "Load uplugins_template";
  }

  dlgBkpSave->InitialDirectory = Application::StartupPath;
  if (dlgBkpSave->ShowDialog() == Windows::Forms::DialogResult::OK) {
    bkpPath = dlgBkpSave->FileName;

    StateUpdate(AppState::Wait);
    if (!bIsTemplate) {
      StatusUpdate("Loading backup...");
    } else {
      StatusUpdate("Loading template...");
    }
    ControlsStateChange(ControlsState::Wait);

    int Counter = 0;
    String^ UEPath = Append(AppForm::cmbUEFolder->SelectedItem->ToString(), "\\Engine\\Plugins\\");
    FileStream^ newStream = gcnew FileStream(bkpPath, FileMode::Open);
    StreamReader^ newReader = gcnew StreamReader(newStream);
    for each (DataRow ^ mDRPlug in dtbPlugins->Rows) {
      mDRPlug["celEnabledByDefault"] = false;
    }
    while (!newReader->EndOfStream)
    {
      String^ sLine = newReader->ReadLine();
      if (!bIsTemplate) {
        if (sLine->Contains(UEPath)) {
          for each (DataRow ^ mDRPlug in dtbPlugins->Rows) {
            if (sLine->Contains(mDRPlug["celPath"]->ToString())) {
              mDRPlug["celEnabledByDefault"] = true;
              Counter++;
            }
          }
        }
      } else {
        for each (DataRow ^ mDRPlug in dtbPlugins->Rows) {
          if (sLine->Contains(mDRPlug["celPath"]->ToString())) {
            mDRPlug["celEnabledByDefault"] = true;
            Counter++;
          }
        }
      }
    }
    newReader->Close();
    newStream->Close();

    ControlsStateChange(ControlsState::Default);
    if (!bIsTemplate) {
      StatusUpdate(Append(Append("Backup loaded. ", Counter.ToString()), " plugins EnabledByDefault."));
    } else {
      StatusUpdate(Append(Append("Template loaded. ", Counter.ToString()), " plugins EnabledByDefault."));
    }
    StateUpdate(AppState::Default);
  }
}


void AppForm::mnuTemplateSave_Click(System::Object^ sender, System::EventArgs^ e)
{
  mnuBackupSave_Click(sender, e);
}

void AppForm::mnuTemplateLoad_Click(System::Object^ sender, System::EventArgs^ e)
{
  mnuBackupLoad_Click(sender, e);
}