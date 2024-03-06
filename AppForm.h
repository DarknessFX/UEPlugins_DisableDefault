#pragma once
///
/// Created by DarknessFX - https://dfx.lv - @DrkFX
/// Source Code at https://github.com/DarknessFX/UEPlugins_DisableDefault
///
/// <attention>
/// Be careful with AppForm.h [Design], VisualStudio Form Designer reset the following static controls:
/// == LINE 49
/*
public: static System::Windows::Forms::ToolStripStatusLabel^ lblStatus;
public: static System::Windows::Forms::ComboBox^ cmbUEFolder;
public: static System::Windows::Forms::Button^ btnBrowse;
public: static System::Windows::Forms::TextBox^ txtSearch;
public: static System::Data::DataTable^ dtbPlugins;
public: static System::Data::DataTable^ dtbPluginsOrig;
public: static System::Windows::Forms::DataGridView^ grdPlugins;
public: static System::Windows::Forms::MenuStrip^ mnuStrip;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuMain;
public: static System::Windows::Forms::Splitter^ splitter1;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuShow;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuShowAll;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuShowEnabled;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuBackup;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuBackupSave;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuBackupLoad;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuTemplate;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuTemplateSave;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuTemplateLoad;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuTemplateMinimal;
public: static System::Windows::Forms::ToolStripDropDownButton^ btnSave;
*/
/// ==
/// If, after using the Form Designer the code don't compile anymore, make sure this static controls are correctly set.
/// See below the common error when this happens:
///     Error Code  : E0245
///     Description	: a nonstatic member reference must be relative to a specific object
/// </attention>


namespace UEPluginsDisableDefault {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

/// <summary>
/// Summary for AppForm
/// </summary>
public ref class AppForm : public System::Windows::Forms::Form
{
public:
AppForm(void)
{
	InitializeComponent();
	//
	//TODO: Add the constructor code here
	//
}
public: static System::Windows::Forms::ToolStripStatusLabel^ lblStatus;
public: static System::Windows::Forms::ComboBox^ cmbUEFolder;
public: static System::Windows::Forms::Button^ btnBrowse;
public: static System::Windows::Forms::TextBox^ txtSearch;
public: static System::Data::DataTable^ dtbPlugins;
public: static System::Data::DataTable^ dtbPluginsOrig;
public: static System::Windows::Forms::DataGridView^ grdPlugins;
public: static System::Windows::Forms::MenuStrip^ mnuStrip;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuMain;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuShow;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuShowAll;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuShowEnabled;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuBackup;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuBackupSave;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuBackupLoad;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuTemplate;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuTemplateSave;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuTemplateLoad;
public: static System::Windows::Forms::ToolStripMenuItem^ mnuTemplateMinimal;
public: static System::Windows::Forms::ToolStripDropDownButton^ btnSave;

protected:
/// <summary>
/// Clean up any resources being used.
/// </summary>
~AppForm()
{
	if (components)
	{
		delete components;
	}
}

private:  
System::Windows::Forms::FlowLayoutPanel^ flwUEFolder;
System::Windows::Forms::Label^ lblUEFolder;
System::Windows::Forms::StatusStrip^ stsStrip;
System::Windows::Forms::FolderBrowserDialog^ dlgBrowse;
System::Data::DataSet^ datPlugins;
System::Data::DataColumn^ celName;
System::Data::DataColumn^ celEnabledDef;
System::Data::DataColumn^ celInstalled;
System::Data::DataColumn^ celFriendlyName;
System::Data::DataColumn^ celDescription;
System::Data::DataColumn^ celCategory;
System::Data::DataColumn^ celVersionName;
System::Data::DataColumn^ celPath;
System::Data::DataColumn^ celIcon;
System::Windows::Forms::DataGridViewCheckBoxColumn^ celEnabledByDefaultDataGridViewCheckBoxColumn;
System::Windows::Forms::DataGridViewCheckBoxColumn^ celInstalledDataGridViewCheckBoxColumn;
System::Windows::Forms::DataGridViewTextBoxColumn^ celCategoryDataGridViewTextBoxColumn;
System::Windows::Forms::DataGridViewImageColumn^ celIconDataGridViewImageColumn;
System::Windows::Forms::DataGridViewTextBoxColumn^ celNameDataGridViewTextBoxColumn;
System::Windows::Forms::DataGridViewTextBoxColumn^ celFriendlyNameDataGridViewTextBoxColumn;
System::Windows::Forms::DataGridViewTextBoxColumn^ celDescriptionDataGridViewTextBoxColumn;
System::Windows::Forms::DataGridViewTextBoxColumn^ celPathDataGridViewTextBoxColumn;
System::Windows::Forms::DataGridViewTextBoxColumn^ celVersionNameDataGridViewTextBoxColumn;
System::Windows::Forms::PictureBox^ imgSearch;
System::Windows::Forms::Splitter^ splitter1;
System::Windows::Forms::Splitter^ splitter2;

/// <summary>
/// Required designer variable.
/// </summary>
System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
/// <summary>
/// Required method for Designer support - do not modify
/// the contents of this method with the code editor.
/// </summary>
void InitializeComponent(void)
{
  System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(AppForm::typeid));
  System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
  this->stsStrip = (gcnew System::Windows::Forms::StatusStrip());
  this->lblStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
  this->btnSave = (gcnew System::Windows::Forms::ToolStripDropDownButton());
  this->flwUEFolder = (gcnew System::Windows::Forms::FlowLayoutPanel());
  this->mnuStrip = (gcnew System::Windows::Forms::MenuStrip());
  this->mnuMain = (gcnew System::Windows::Forms::ToolStripMenuItem());
  this->mnuShow = (gcnew System::Windows::Forms::ToolStripMenuItem());
  this->mnuShowAll = (gcnew System::Windows::Forms::ToolStripMenuItem());
  this->mnuShowEnabled = (gcnew System::Windows::Forms::ToolStripMenuItem());
  this->mnuBackup = (gcnew System::Windows::Forms::ToolStripMenuItem());
  this->mnuBackupSave = (gcnew System::Windows::Forms::ToolStripMenuItem());
  this->mnuBackupLoad = (gcnew System::Windows::Forms::ToolStripMenuItem());
  this->mnuTemplate = (gcnew System::Windows::Forms::ToolStripMenuItem());
  this->mnuTemplateSave = (gcnew System::Windows::Forms::ToolStripMenuItem());
  this->mnuTemplateLoad = (gcnew System::Windows::Forms::ToolStripMenuItem());
  this->mnuTemplateMinimal = (gcnew System::Windows::Forms::ToolStripMenuItem());
  this->splitter1 = (gcnew System::Windows::Forms::Splitter());
  this->lblUEFolder = (gcnew System::Windows::Forms::Label());
  this->cmbUEFolder = (gcnew System::Windows::Forms::ComboBox());
  this->btnBrowse = (gcnew System::Windows::Forms::Button());
  this->imgSearch = (gcnew System::Windows::Forms::PictureBox());
  this->txtSearch = (gcnew System::Windows::Forms::TextBox());
  this->dlgBrowse = (gcnew System::Windows::Forms::FolderBrowserDialog());
  this->datPlugins = (gcnew System::Data::DataSet());
  this->dtbPlugins = (gcnew System::Data::DataTable());
  this->celName = (gcnew System::Data::DataColumn());
  this->celEnabledDef = (gcnew System::Data::DataColumn());
  this->celInstalled = (gcnew System::Data::DataColumn());
  this->celFriendlyName = (gcnew System::Data::DataColumn());
  this->celDescription = (gcnew System::Data::DataColumn());
  this->celCategory = (gcnew System::Data::DataColumn());
  this->celVersionName = (gcnew System::Data::DataColumn());
  this->celPath = (gcnew System::Data::DataColumn());
  this->celIcon = (gcnew System::Data::DataColumn());
  this->dtbPluginsOrig = (gcnew System::Data::DataTable());
  this->grdPlugins = (gcnew System::Windows::Forms::DataGridView());
  this->celEnabledByDefaultDataGridViewCheckBoxColumn = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
  this->celInstalledDataGridViewCheckBoxColumn = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
  this->celCategoryDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
  this->celIconDataGridViewImageColumn = (gcnew System::Windows::Forms::DataGridViewImageColumn());
  this->celNameDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
  this->celFriendlyNameDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
  this->celDescriptionDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
  this->celPathDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
  this->celVersionNameDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
  this->splitter2 = (gcnew System::Windows::Forms::Splitter());
  this->stsStrip->SuspendLayout();
  this->flwUEFolder->SuspendLayout();
  this->mnuStrip->SuspendLayout();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->imgSearch))->BeginInit();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->datPlugins))->BeginInit();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dtbPlugins))->BeginInit();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dtbPluginsOrig))->BeginInit();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdPlugins))->BeginInit();
  this->SuspendLayout();
  // 
  // stsStrip
  // 
  this->stsStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->lblStatus, this->btnSave });
  this->stsStrip->Location = System::Drawing::Point(0, 405);
  this->stsStrip->Name = L"stsStrip";
  this->stsStrip->Size = System::Drawing::Size(963, 22);
  this->stsStrip->TabIndex = 1;
  // 
  // lblStatus
  // 
  this->lblStatus->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top)
    | System::Windows::Forms::ToolStripStatusLabelBorderSides::Right)
    | System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
  this->lblStatus->BorderStyle = System::Windows::Forms::Border3DStyle::SunkenInner;
  this->lblStatus->Font = (gcnew System::Drawing::Font(L"Roboto", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
    static_cast<System::Byte>(0)));
  this->lblStatus->Name = L"lblStatus";
  this->lblStatus->Overflow = System::Windows::Forms::ToolStripItemOverflow::Never;
  this->lblStatus->Size = System::Drawing::Size(834, 17);
  this->lblStatus->Spring = true;
  this->lblStatus->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
  // 
  // btnSave
  // 
  this->btnSave->BackColor = System::Drawing::SystemColors::Control;
  this->btnSave->Enabled = false;
  this->btnSave->Font = (gcnew System::Drawing::Font(L"Roboto", 9, System::Drawing::FontStyle::Bold));
  this->btnSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSave.Image")));
  this->btnSave->ImageTransparentColor = System::Drawing::Color::Magenta;
  this->btnSave->Margin = System::Windows::Forms::Padding(4, 2, 4, 0);
  this->btnSave->Name = L"btnSave";
  this->btnSave->ShowDropDownArrow = false;
  this->btnSave->Size = System::Drawing::Size(106, 20);
  this->btnSave->Text = L"Apply changes";
  this->btnSave->ToolTipText = L"Write your changes to .uplugin files.";
  this->btnSave->Click += gcnew System::EventHandler(this, &AppForm::btnSave_Click);
  // 
  // flwUEFolder
  // 
  this->flwUEFolder->AutoSize = true;
  this->flwUEFolder->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->flwUEFolder->Controls->Add(this->mnuStrip);
  this->flwUEFolder->Controls->Add(this->splitter1);
  this->flwUEFolder->Controls->Add(this->lblUEFolder);
  this->flwUEFolder->Controls->Add(this->cmbUEFolder);
  this->flwUEFolder->Controls->Add(this->btnBrowse);
  this->flwUEFolder->Controls->Add(this->splitter2);
  this->flwUEFolder->Controls->Add(this->imgSearch);
  this->flwUEFolder->Controls->Add(this->txtSearch);
  this->flwUEFolder->Dock = System::Windows::Forms::DockStyle::Top;
  this->flwUEFolder->Location = System::Drawing::Point(0, 0);
  this->flwUEFolder->Name = L"flwUEFolder";
  this->flwUEFolder->Size = System::Drawing::Size(963, 30);
  this->flwUEFolder->TabIndex = 2;
  this->flwUEFolder->WrapContents = false;
  // 
  // mnuStrip
  // 
  this->mnuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->mnuMain });
  this->mnuStrip->Location = System::Drawing::Point(0, 0);
  this->mnuStrip->Name = L"mnuStrip";
  this->mnuStrip->Padding = System::Windows::Forms::Padding(0);
  this->mnuStrip->Size = System::Drawing::Size(57, 26);
  this->mnuStrip->TabIndex = 6;
  this->mnuStrip->Text = L"mnuStrip";
  // 
  // mnuMain
  // 
  this->mnuMain->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
    this->mnuShow, this->mnuBackup,
      this->mnuTemplate
  });
  this->mnuMain->Font = (gcnew System::Drawing::Font(L"Roboto", 8.25F, System::Drawing::FontStyle::Bold));
  this->mnuMain->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"mnuMain.Image")));
  this->mnuMain->Margin = System::Windows::Forms::Padding(0, 6, 0, 0);
  this->mnuMain->Name = L"mnuMain";
  this->mnuMain->Padding = System::Windows::Forms::Padding(0);
  this->mnuMain->Size = System::Drawing::Size(55, 20);
  this->mnuMain->Text = L"Menu";
  // 
  // mnuShow
  // 
  this->mnuShow->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
    this->mnuShowAll,
      this->mnuShowEnabled
  });
  this->mnuShow->Name = L"mnuShow";
  this->mnuShow->Size = System::Drawing::Size(122, 22);
  this->mnuShow->Text = L"Filter";
  this->mnuShow->MouseHover += gcnew System::EventHandler(this, &AppForm::mnuShow_MouseHover);
  // 
  // mnuShowAll
  // 
  this->mnuShowAll->Checked = true;
  this->mnuShowAll->CheckState = System::Windows::Forms::CheckState::Checked;
  this->mnuShowAll->Name = L"mnuShowAll";
  this->mnuShowAll->Size = System::Drawing::Size(169, 22);
  this->mnuShowAll->Text = L"Show All";
  this->mnuShowAll->Click += gcnew System::EventHandler(this, &AppForm::mnuShowAll_Click);
  // 
  // mnuShowEnabled
  // 
  this->mnuShowEnabled->Name = L"mnuShowEnabled";
  this->mnuShowEnabled->Size = System::Drawing::Size(169, 22);
  this->mnuShowEnabled->Text = L"Show Enabled Only";
  this->mnuShowEnabled->Click += gcnew System::EventHandler(this, &AppForm::mnuShowEnabled_Click);
  // 
  // mnuBackup
  // 
  this->mnuBackup->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
    this->mnuBackupSave,
    this->mnuBackupLoad
  });
  this->mnuBackup->Name = L"mnuBackup";
  this->mnuBackup->Size = System::Drawing::Size(122, 22);
  this->mnuBackup->Text = L"Backup";
  this->mnuBackup->MouseHover += gcnew System::EventHandler(this, &AppForm::mnuBackup_MouseHover);
  // 
  // mnuBackupSave
  // 
  this->mnuBackupSave->Name = L"mnuBackupSave";
  this->mnuBackupSave->Size = System::Drawing::Size(138, 22);
  this->mnuBackupSave->Text = L"Save backup";
  this->mnuBackupSave->Click += gcnew System::EventHandler(this, &AppForm::mnuBackupSave_Click);
  // 
  // mnuBackupLoad
  // 
  this->mnuBackupLoad->Name = L"mnuBackupLoad";
  this->mnuBackupLoad->Size = System::Drawing::Size(138, 22);
  this->mnuBackupLoad->Text = L"Load backup";
  this->mnuBackupLoad->Click += gcnew System::EventHandler(this, &AppForm::mnuBackupLoad_Click);
  // 
  // mnuTemplate
  // 
  this->mnuTemplate->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
    this->mnuTemplateSave,
      this->mnuTemplateLoad, this->mnuTemplateMinimal
  });
  this->mnuTemplate->Name = L"mnuTemplate";
  this->mnuTemplate->Size = System::Drawing::Size(122, 22);
  this->mnuTemplate->Text = L"Template";
  this->mnuTemplate->MouseHover += gcnew System::EventHandler(this, &AppForm::mnuTemplate_MouseHover);
  // 
  // mnuTemplateSave
  // 
  this->mnuTemplateSave->Name = L"mnuTemplateSave";
  this->mnuTemplateSave->Size = System::Drawing::Size(147, 22);
  this->mnuTemplateSave->Text = L"Save template";
  this->mnuTemplateSave->Click += gcnew System::EventHandler(this, &AppForm::mnuTemplateSave_Click);
  // 
  // mnuTemplateLoad
  // 
  this->mnuTemplateLoad->Name = L"mnuTemplateLoad";
  this->mnuTemplateLoad->Size = System::Drawing::Size(147, 22);
  this->mnuTemplateLoad->Text = L"Load template";
  this->mnuTemplateLoad->Click += gcnew System::EventHandler(this, &AppForm::mnuTemplateLoad_Click);
  // 
  // mnuTemplateMinimal
  // 
  this->mnuTemplateMinimal->Name = L"mnuTemplateMinimal";
  this->mnuTemplateMinimal->Size = System::Drawing::Size(147, 22);
  this->mnuTemplateMinimal->Text = L"Apply Minimal";
  this->mnuTemplateMinimal->Click += gcnew System::EventHandler(this, &AppForm::mnuTemplateMinimal_Click);
  // 
  // splitter1
  // 
  this->splitter1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
  this->splitter1->Location = System::Drawing::Point(60, 3);
  this->splitter1->Name = L"splitter1";
  this->splitter1->Size = System::Drawing::Size(2, 24);
  this->splitter1->TabIndex = 7;
  this->splitter1->TabStop = false;
  // 
  // lblUEFolder
  // 
  this->lblUEFolder->AutoSize = true;
  this->lblUEFolder->Dock = System::Windows::Forms::DockStyle::Left;
  this->lblUEFolder->Font = (gcnew System::Drawing::Font(L"Roboto", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
    static_cast<System::Byte>(0)));
  this->lblUEFolder->Location = System::Drawing::Point(72, 10);
  this->lblUEFolder->Margin = System::Windows::Forms::Padding(3, 10, 3, 0);
  this->lblUEFolder->Name = L"lblUEFolder";
  this->lblUEFolder->Size = System::Drawing::Size(109, 20);
  this->lblUEFolder->TabIndex = 0;
  this->lblUEFolder->Text = L"Unreal Engine Folder";
  // 
  // cmbUEFolder
  // 
  this->cmbUEFolder->Dock = System::Windows::Forms::DockStyle::Fill;
  this->cmbUEFolder->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
  this->cmbUEFolder->FlatStyle = System::Windows::Forms::FlatStyle::System;
  this->cmbUEFolder->Font = (gcnew System::Drawing::Font(L"Roboto", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
    static_cast<System::Byte>(0)));
  this->cmbUEFolder->Location = System::Drawing::Point(187, 5);
  this->cmbUEFolder->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
  this->cmbUEFolder->Name = L"cmbUEFolder";
  this->cmbUEFolder->Size = System::Drawing::Size(240, 21);
  this->cmbUEFolder->TabIndex = 1;
  this->cmbUEFolder->SelectedIndexChanged += gcnew System::EventHandler(this, &AppForm::cmbUEFolder_SelectedIndexChanged);
  // 
  // btnBrowse
  // 
  this->btnBrowse->AutoSize = true;
  this->btnBrowse->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->btnBrowse->Dock = System::Windows::Forms::DockStyle::Right;
  this->btnBrowse->Font = (gcnew System::Drawing::Font(L"Roboto", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
    static_cast<System::Byte>(0)));
  this->btnBrowse->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnBrowse.Image")));
  this->btnBrowse->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
  this->btnBrowse->Location = System::Drawing::Point(433, 3);
  this->btnBrowse->Name = L"btnBrowse";
  this->btnBrowse->Size = System::Drawing::Size(72, 24);
  this->btnBrowse->TabIndex = 2;
  this->btnBrowse->Text = L"Browse";
  this->btnBrowse->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
  this->btnBrowse->UseVisualStyleBackColor = true;
  this->btnBrowse->Click += gcnew System::EventHandler(this, &AppForm::btnBrowse_Click);
  // 
  // splitter2
  // 
  this->splitter2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
  this->splitter2->Location = System::Drawing::Point(654, 3);
  this->splitter2->Name = L"splitter2";
  this->splitter2->Size = System::Drawing::Size(2, 24);
  this->splitter2->TabIndex = 9;
  this->splitter2->TabStop = false;
  // 
  // imgSearch
  // 
  this->imgSearch->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"imgSearch.BackgroundImage")));
  this->imgSearch->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
  this->imgSearch->Location = System::Drawing::Point(508, 5);
  this->imgSearch->Margin = System::Windows::Forms::Padding(0, 5, 0, 0);
  this->imgSearch->Name = L"imgSearch";
  this->imgSearch->Size = System::Drawing::Size(20, 20);
  this->imgSearch->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
  this->imgSearch->TabIndex = 8;
  this->imgSearch->TabStop = false;
  // 
  // txtSearch
  // 
  this->txtSearch->AcceptsReturn = true;
  this->txtSearch->AcceptsTab = true;
  this->txtSearch->Dock = System::Windows::Forms::DockStyle::Top;
  this->txtSearch->Font = (gcnew System::Drawing::Font(L"Roboto", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
    static_cast<System::Byte>(0)));
  this->txtSearch->HideSelection = false;
  this->txtSearch->Location = System::Drawing::Point(528, 5);
  this->txtSearch->Margin = System::Windows::Forms::Padding(0, 5, 3, 0);
  this->txtSearch->MaxLength = 200;
  this->txtSearch->Name = L"txtSearch";
  this->txtSearch->Size = System::Drawing::Size(120, 21);
  this->txtSearch->TabIndex = 3;
  this->txtSearch->WordWrap = false;
  this->txtSearch->GotFocus += gcnew System::EventHandler(this, &AppForm::txtSearch_GotFocus);
  this->txtSearch->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &AppForm::txtSearch_KeyUp);
  // 
  // dlgBrowse
  // 
  this->dlgBrowse->RootFolder = System::Environment::SpecialFolder::MyComputer;
  this->dlgBrowse->ShowNewFolderButton = false;
  // 
  // datPlugins
  // 
  this->datPlugins->DataSetName = L"datPlugins";
  this->datPlugins->Tables->AddRange(gcnew cli::array< System::Data::DataTable^  >(1) { this->dtbPlugins });
  // 
  // dtbPlugins
  // 
  this->dtbPlugins->CaseSensitive = false;
  this->dtbPlugins->Columns->AddRange(gcnew cli::array< System::Data::DataColumn^  >(9) {
    this->celName, this->celEnabledDef,
      this->celInstalled, this->celFriendlyName, this->celDescription, this->celCategory, this->celVersionName, this->celPath, this->celIcon
  });
  cli::array< System::String^ >^ __mcTemp__1 = gcnew cli::array< System::String^  >(1) { L"celName" };
  this->dtbPlugins->Constraints->AddRange(gcnew cli::array< System::Data::Constraint^  >(1) {
    (gcnew System::Data::UniqueConstraint(L"Constraint1",
      __mcTemp__1, true))
  });
  this->dtbPlugins->PrimaryKey = gcnew cli::array< System::Data::DataColumn^  >(1) { this->celName };
  this->dtbPlugins->TableName = L"dtbPlugins";
  // 
  // celName
  // 
  this->celName->AllowDBNull = false;
  this->celName->Caption = L"Name";
  this->celName->ColumnName = L"celName";
  this->celName->DefaultValue = L"";
  this->celName->MaxLength = 50;
  // 
  // celEnabledDef
  // 
  this->celEnabledDef->AllowDBNull = false;
  this->celEnabledDef->ColumnName = L"celEnabledByDefault";
  this->celEnabledDef->DataType = System::Boolean::typeid;
  this->celEnabledDef->DefaultValue = false;
  // 
  // celInstalled
  // 
  this->celInstalled->AllowDBNull = false;
  this->celInstalled->ColumnName = L"celInstalled";
  this->celInstalled->DataType = System::Boolean::typeid;
  this->celInstalled->DefaultValue = false;
  // 
  // celFriendlyName
  // 
  this->celFriendlyName->Caption = L"Friendly Name";
  this->celFriendlyName->ColumnName = L"celFriendlyName";
  // 
  // celDescription
  // 
  this->celDescription->ColumnName = L"celDescription";
  // 
  // celCategory
  // 
  this->celCategory->ColumnName = L"celCategory";
  // 
  // celVersionName
  // 
  this->celVersionName->Caption = L"Version";
  this->celVersionName->ColumnName = L"celVersionName";
  // 
  // celPath
  // 
  this->celPath->ColumnName = L"celPath";
  // 
  // celIcon
  // 
  this->celIcon->ColumnName = L"celIcon";
  this->celIcon->DataType = System::Object::typeid;
  // 
  // dtbPluginsOrig
  // 
  this->dtbPluginsOrig->CaseSensitive = true;
  this->dtbPluginsOrig->TableName = L"dtbPluginsOrig";
  // 
  // grdPlugins
  // 
  this->grdPlugins->AllowUserToAddRows = false;
  this->grdPlugins->AllowUserToDeleteRows = false;
  this->grdPlugins->AllowUserToResizeRows = false;
  this->grdPlugins->AutoGenerateColumns = false;
  this->grdPlugins->ClipboardCopyMode = System::Windows::Forms::DataGridViewClipboardCopyMode::EnableWithoutHeaderText;
  dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
  dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
  dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Roboto", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
    static_cast<System::Byte>(0)));
  dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
  dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
  dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
  dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
  this->grdPlugins->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
  this->grdPlugins->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
  this->grdPlugins->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(9) {
    this->celEnabledByDefaultDataGridViewCheckBoxColumn,
    this->celInstalledDataGridViewCheckBoxColumn, this->celCategoryDataGridViewTextBoxColumn, this->celIconDataGridViewImageColumn,
    this->celNameDataGridViewTextBoxColumn, this->celFriendlyNameDataGridViewTextBoxColumn, this->celDescriptionDataGridViewTextBoxColumn,
    this->celPathDataGridViewTextBoxColumn, this->celVersionNameDataGridViewTextBoxColumn
  });
  this->grdPlugins->DataMember = L"dtbPlugins";
  this->grdPlugins->DataSource = this->datPlugins;
  this->grdPlugins->Dock = System::Windows::Forms::DockStyle::Fill;
  this->grdPlugins->Location = System::Drawing::Point(0, 30);
  this->grdPlugins->MultiSelect = false;
  this->grdPlugins->Name = L"grdPlugins";
  this->grdPlugins->RowHeadersVisible = false;
  this->grdPlugins->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::CellSelect;
  this->grdPlugins->Size = System::Drawing::Size(963, 375);
  this->grdPlugins->TabIndex = 4;
  this->grdPlugins->VirtualMode = true;
  this->grdPlugins->CurrentCellDirtyStateChanged += gcnew System::EventHandler(this, &AppForm::grdPlugins_CurrentCellDirtyStateChanged);
  this->grdPlugins->CellDoubleClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &AppForm::grdPlugins_CellDoubleClick);
  // 
  // celEnabledByDefaultDataGridViewCheckBoxColumn
  // 
  this->celEnabledByDefaultDataGridViewCheckBoxColumn->DataPropertyName = L"celEnabledByDefault";
  this->celEnabledByDefaultDataGridViewCheckBoxColumn->FillWeight = 60;
  this->celEnabledByDefaultDataGridViewCheckBoxColumn->HeaderText = L"ByDefault";
  this->celEnabledByDefaultDataGridViewCheckBoxColumn->Name = L"celEnabledByDefaultDataGridViewCheckBoxColumn";
  this->celEnabledByDefaultDataGridViewCheckBoxColumn->Width = 60;
  // 
  // celInstalledDataGridViewCheckBoxColumn
  // 
  this->celInstalledDataGridViewCheckBoxColumn->DataPropertyName = L"celInstalled";
  this->celInstalledDataGridViewCheckBoxColumn->FillWeight = 60;
  this->celInstalledDataGridViewCheckBoxColumn->HeaderText = L"Installed";
  this->celInstalledDataGridViewCheckBoxColumn->Name = L"celInstalledDataGridViewCheckBoxColumn";
  //this->celInstalledDataGridViewCheckBoxColumn->ReadOnly = true;
  this->celInstalledDataGridViewCheckBoxColumn->Width = 60;
  // 
  // celCategoryDataGridViewTextBoxColumn
  // 
  this->celCategoryDataGridViewTextBoxColumn->DataPropertyName = L"celCategory";
  this->celCategoryDataGridViewTextBoxColumn->HeaderText = L"Category";
  this->celCategoryDataGridViewTextBoxColumn->Name = L"celCategoryDataGridViewTextBoxColumn";
  this->celCategoryDataGridViewTextBoxColumn->ReadOnly = true;
  // 
  // celIconDataGridViewImageColumn
  // 
  this->celIconDataGridViewImageColumn->DataPropertyName = L"celIcon";
  this->celIconDataGridViewImageColumn->FillWeight = 30;
  this->celIconDataGridViewImageColumn->HeaderText = L"Icon";
  this->celIconDataGridViewImageColumn->ImageLayout = System::Windows::Forms::DataGridViewImageCellLayout::Zoom;
  this->celIconDataGridViewImageColumn->Name = L"celIconDataGridViewImageColumn";
  this->celIconDataGridViewImageColumn->ReadOnly = true;
  this->celIconDataGridViewImageColumn->Width = 30;
  // 
  // celNameDataGridViewTextBoxColumn
  // 
  this->celNameDataGridViewTextBoxColumn->DataPropertyName = L"celName";
  this->celNameDataGridViewTextBoxColumn->FillWeight = 170;
  this->celNameDataGridViewTextBoxColumn->HeaderText = L"Name";
  this->celNameDataGridViewTextBoxColumn->Name = L"celNameDataGridViewTextBoxColumn";
  this->celNameDataGridViewTextBoxColumn->ReadOnly = true;
  this->celNameDataGridViewTextBoxColumn->Visible = false;
  this->celNameDataGridViewTextBoxColumn->Width = 170;
  // 
  // celFriendlyNameDataGridViewTextBoxColumn
  // 
  this->celFriendlyNameDataGridViewTextBoxColumn->DataPropertyName = L"celFriendlyName";
  this->celFriendlyNameDataGridViewTextBoxColumn->FillWeight = 170;
  this->celFriendlyNameDataGridViewTextBoxColumn->HeaderText = L"Name";
  this->celFriendlyNameDataGridViewTextBoxColumn->Name = L"celFriendlyNameDataGridViewTextBoxColumn";
  this->celFriendlyNameDataGridViewTextBoxColumn->ReadOnly = true;
  this->celFriendlyNameDataGridViewTextBoxColumn->Width = 170;
  // 
  // celDescriptionDataGridViewTextBoxColumn
  // 
  this->celDescriptionDataGridViewTextBoxColumn->DataPropertyName = L"celDescription";
  this->celDescriptionDataGridViewTextBoxColumn->FillWeight = 240;
  this->celDescriptionDataGridViewTextBoxColumn->HeaderText = L"Description";
  this->celDescriptionDataGridViewTextBoxColumn->Name = L"celDescriptionDataGridViewTextBoxColumn";
  this->celDescriptionDataGridViewTextBoxColumn->ReadOnly = true;
  this->celDescriptionDataGridViewTextBoxColumn->Width = 240;
  // 
  // celPathDataGridViewTextBoxColumn
  // 
  this->celPathDataGridViewTextBoxColumn->DataPropertyName = L"celPath";
  this->celPathDataGridViewTextBoxColumn->FillWeight = 240;
  this->celPathDataGridViewTextBoxColumn->HeaderText = L"Path";
  this->celPathDataGridViewTextBoxColumn->Name = L"celPathDataGridViewTextBoxColumn";
  this->celPathDataGridViewTextBoxColumn->ReadOnly = true;
  this->celPathDataGridViewTextBoxColumn->Width = 240;
  // 
  // celVersionNameDataGridViewTextBoxColumn
  // 
  this->celVersionNameDataGridViewTextBoxColumn->DataPropertyName = L"celVersionName";
  this->celVersionNameDataGridViewTextBoxColumn->FillWeight = 40;
  this->celVersionNameDataGridViewTextBoxColumn->HeaderText = L"Ver";
  this->celVersionNameDataGridViewTextBoxColumn->Name = L"celVersionNameDataGridViewTextBoxColumn";
  this->celVersionNameDataGridViewTextBoxColumn->ReadOnly = true;
  this->celVersionNameDataGridViewTextBoxColumn->Width = 40;
  // 
  // AppForm
  // 
  this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
  this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
  this->ClientSize = System::Drawing::Size(963, 427);
  this->Controls->Add(this->grdPlugins);
  this->Controls->Add(this->flwUEFolder);
  this->Controls->Add(this->stsStrip);
  this->Font = (gcnew System::Drawing::Font(L"Roboto", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
    static_cast<System::Byte>(0)));
  this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
  this->MinimumSize = System::Drawing::Size(456, 200);
  this->Name = L"AppForm";
  this->Text = L"UEPlugins_DisableDefault";
  this->Load += gcnew System::EventHandler(this, &AppForm::AppForm_Load);
  this->SizeChanged += gcnew System::EventHandler(this, &AppForm::AppForm_SizeChanged);
  this->stsStrip->ResumeLayout(false);
  this->stsStrip->PerformLayout();
  this->flwUEFolder->ResumeLayout(false);
  this->flwUEFolder->PerformLayout();
  this->mnuStrip->ResumeLayout(false);
  this->mnuStrip->PerformLayout();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->imgSearch))->EndInit();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->datPlugins))->EndInit();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dtbPlugins))->EndInit();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dtbPluginsOrig))->EndInit();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdPlugins))->EndInit();
  this->ResumeLayout(false);
  this->PerformLayout();

}
#pragma endregion

void AppForm_Load ( System::Object^ sender, System::EventArgs^ e );
void AppForm_SizeChanged ( System::Object^ sender, System::EventArgs^ e );

void cmbUEFolder_SelectedIndexChanged ( System::Object^ sender, System::EventArgs^ e );
void btnBrowse_Click ( System::Object^ sender, System::EventArgs^ e );
void btnSave_Click ( System::Object^ sender, System::EventArgs^ e );
void grdPlugins_CurrentCellDirtyStateChanged ( System::Object^ sender, System::EventArgs^ e );
void grdPlugins_CellDoubleClick ( System::Object^ sender, DataGridViewCellEventArgs^ e );
void txtSearch_GotFocus(System::Object^ sender, System::EventArgs^ e);
void txtSearch_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);

void mnuShow_MouseHover(System::Object^ sender, System::EventArgs^ e);
void mnuShowAll_Click(System::Object^ sender, System::EventArgs^ e);
void mnuShowEnabled_Click(System::Object^ sender, System::EventArgs^ e);
void mnuBackup_MouseHover(System::Object^ sender, System::EventArgs^ e);
void mnuBackupSave_Click(System::Object^ sender, System::EventArgs^ e);
void mnuBackupLoad_Click(System::Object^ sender, System::EventArgs^ e);
void mnuTemplate_MouseHover(System::Object^ sender, System::EventArgs^ e);
void mnuTemplateSave_Click(System::Object^ sender, System::EventArgs^ e);
void mnuTemplateLoad_Click(System::Object^ sender, System::EventArgs^ e);
void mnuTemplateMinimal_Click(System::Object^ sender, System::EventArgs^ e);

void UpdateFlow();

};
};

// DFX Main functions
using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;

enum class AppState 
{
    Default  = 0,
    Wait     = 1
};
void StateUpdate(AppState State);
void StatusUpdate(System::String^ Message);


String^ Append(String^ str0, System::String^ str1);
String^ ReplaceSlashes(String^ Path);

void Searching(String^ Path);
void FindUPlugin(String^ Path);
void AddUPlugin(String^ FileUPlugin);
void ReadUPlugin(String^ FileUPlugin, DataRow^& mDataRow);
void GetJSONValue(String^& str0);

int CountEnabledByDefault();
bool IsIgnoredFolder(String^ Path);
void CheckAcess(String^ FileUPlugin);

enum class ControlsState 
{
    Default  = true,
    Wait     = false
};
void ControlsStateChange(ControlsState State);

void BackupAll();
List<String^>^ FindAllUPlugins(String^ Path);
