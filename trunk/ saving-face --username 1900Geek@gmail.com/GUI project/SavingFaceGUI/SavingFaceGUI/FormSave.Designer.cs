namespace SavingFaceGUI
{
    partial class FormSave
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormSave));
            this.labelFirstName = new System.Windows.Forms.Label();
            this.labelEmail = new System.Windows.Forms.Label();
            this.firstNameTB = new System.Windows.Forms.TextBox();
            this.emailTB = new System.Windows.Forms.TextBox();
            this.userImagePB = new System.Windows.Forms.PictureBox();
            this.takePictureBTN = new System.Windows.Forms.Button();
            this.nextBTN = new System.Windows.Forms.Button();
            this.cancelBTN = new System.Windows.Forms.Button();
            this.labelLastName = new System.Windows.Forms.Label();
            this.lastNameTB = new System.Windows.Forms.TextBox();
            this.maleRB = new System.Windows.Forms.RadioButton();
            this.femaleRB = new System.Windows.Forms.RadioButton();
            this.genderRBGroup = new System.Windows.Forms.GroupBox();
            this.userInfoGroup = new System.Windows.Forms.GroupBox();
            this.infoLBL = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.userImagePB)).BeginInit();
            this.genderRBGroup.SuspendLayout();
            this.userInfoGroup.SuspendLayout();
            this.SuspendLayout();
            // 
            // labelFirstName
            // 
            this.labelFirstName.AutoSize = true;
            this.labelFirstName.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelFirstName.Location = new System.Drawing.Point(17, 37);
            this.labelFirstName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelFirstName.Name = "labelFirstName";
            this.labelFirstName.Size = new System.Drawing.Size(97, 20);
            this.labelFirstName.TabIndex = 0;
            this.labelFirstName.Text = "First Name:";
            // 
            // labelEmail
            // 
            this.labelEmail.AutoSize = true;
            this.labelEmail.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelEmail.Location = new System.Drawing.Point(58, 97);
            this.labelEmail.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelEmail.Name = "labelEmail";
            this.labelEmail.Size = new System.Drawing.Size(56, 20);
            this.labelEmail.TabIndex = 1;
            this.labelEmail.Text = "Email:";
            // 
            // firstNameTB
            // 
            this.firstNameTB.Location = new System.Drawing.Point(122, 35);
            this.firstNameTB.Margin = new System.Windows.Forms.Padding(4);
            this.firstNameTB.Name = "firstNameTB";
            this.firstNameTB.Size = new System.Drawing.Size(222, 22);
            this.firstNameTB.TabIndex = 2;
            // 
            // emailTB
            // 
            this.emailTB.Location = new System.Drawing.Point(122, 97);
            this.emailTB.Margin = new System.Windows.Forms.Padding(4);
            this.emailTB.Name = "emailTB";
            this.emailTB.Size = new System.Drawing.Size(222, 22);
            this.emailTB.TabIndex = 3;
            // 
            // userImagePB
            // 
            this.userImagePB.Image = ((System.Drawing.Image)(resources.GetObject("userImagePB.Image")));
            this.userImagePB.Location = new System.Drawing.Point(585, 13);
            this.userImagePB.Margin = new System.Windows.Forms.Padding(4);
            this.userImagePB.Name = "userImagePB";
            this.userImagePB.Size = new System.Drawing.Size(197, 258);
            this.userImagePB.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.userImagePB.TabIndex = 5;
            this.userImagePB.TabStop = false;
            // 
            // takePictureBTN
            // 
            this.takePictureBTN.Font = new System.Drawing.Font("Book Antiqua", 13.8F);
            this.takePictureBTN.Location = new System.Drawing.Point(585, 279);
            this.takePictureBTN.Margin = new System.Windows.Forms.Padding(4);
            this.takePictureBTN.Name = "takePictureBTN";
            this.takePictureBTN.Size = new System.Drawing.Size(197, 36);
            this.takePictureBTN.TabIndex = 6;
            this.takePictureBTN.Text = "Take Picture";
            this.takePictureBTN.UseVisualStyleBackColor = true;
            // 
            // nextBTN
            // 
            this.nextBTN.Font = new System.Drawing.Font("Book Antiqua", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nextBTN.Location = new System.Drawing.Point(585, 363);
            this.nextBTN.Margin = new System.Windows.Forms.Padding(4);
            this.nextBTN.Name = "nextBTN";
            this.nextBTN.Size = new System.Drawing.Size(197, 39);
            this.nextBTN.TabIndex = 7;
            this.nextBTN.Text = "Next";
            this.nextBTN.UseVisualStyleBackColor = true;
            // 
            // cancelBTN
            // 
            this.cancelBTN.Font = new System.Drawing.Font("Book Antiqua", 13.8F);
            this.cancelBTN.Location = new System.Drawing.Point(34, 363);
            this.cancelBTN.Margin = new System.Windows.Forms.Padding(4);
            this.cancelBTN.Name = "cancelBTN";
            this.cancelBTN.Size = new System.Drawing.Size(197, 39);
            this.cancelBTN.TabIndex = 8;
            this.cancelBTN.Text = "Cancel";
            this.cancelBTN.UseVisualStyleBackColor = true;
            this.cancelBTN.Click += new System.EventHandler(this.buttonBack_Click);
            // 
            // labelLastName
            // 
            this.labelLastName.AutoSize = true;
            this.labelLastName.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelLastName.Location = new System.Drawing.Point(18, 66);
            this.labelLastName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelLastName.Name = "labelLastName";
            this.labelLastName.Size = new System.Drawing.Size(96, 20);
            this.labelLastName.TabIndex = 10;
            this.labelLastName.Text = "Last Name:";
            // 
            // lastNameTB
            // 
            this.lastNameTB.Location = new System.Drawing.Point(122, 66);
            this.lastNameTB.Margin = new System.Windows.Forms.Padding(4);
            this.lastNameTB.Name = "lastNameTB";
            this.lastNameTB.Size = new System.Drawing.Size(222, 22);
            this.lastNameTB.TabIndex = 12;
            // 
            // maleRB
            // 
            this.maleRB.AutoSize = true;
            this.maleRB.Location = new System.Drawing.Point(27, 31);
            this.maleRB.Margin = new System.Windows.Forms.Padding(4);
            this.maleRB.Name = "maleRB";
            this.maleRB.Size = new System.Drawing.Size(59, 21);
            this.maleRB.TabIndex = 13;
            this.maleRB.TabStop = true;
            this.maleRB.Text = "Male";
            this.maleRB.UseVisualStyleBackColor = true;
            // 
            // femaleRB
            // 
            this.femaleRB.AutoSize = true;
            this.femaleRB.Location = new System.Drawing.Point(27, 60);
            this.femaleRB.Margin = new System.Windows.Forms.Padding(4);
            this.femaleRB.Name = "femaleRB";
            this.femaleRB.Size = new System.Drawing.Size(75, 21);
            this.femaleRB.TabIndex = 14;
            this.femaleRB.TabStop = true;
            this.femaleRB.Text = "Female";
            this.femaleRB.UseVisualStyleBackColor = true;
            // 
            // genderRBGroup
            // 
            this.genderRBGroup.Controls.Add(this.maleRB);
            this.genderRBGroup.Controls.Add(this.femaleRB);
            this.genderRBGroup.Location = new System.Drawing.Point(389, 35);
            this.genderRBGroup.Name = "genderRBGroup";
            this.genderRBGroup.Size = new System.Drawing.Size(127, 106);
            this.genderRBGroup.TabIndex = 15;
            this.genderRBGroup.TabStop = false;
            this.genderRBGroup.Text = "Gender";
            // 
            // userInfoGroup
            // 
            this.userInfoGroup.Controls.Add(this.infoLBL);
            this.userInfoGroup.Controls.Add(this.label2);
            this.userInfoGroup.Controls.Add(this.label1);
            this.userInfoGroup.Controls.Add(this.labelFirstName);
            this.userInfoGroup.Controls.Add(this.genderRBGroup);
            this.userInfoGroup.Controls.Add(this.labelLastName);
            this.userInfoGroup.Controls.Add(this.lastNameTB);
            this.userInfoGroup.Controls.Add(this.firstNameTB);
            this.userInfoGroup.Controls.Add(this.labelEmail);
            this.userInfoGroup.Controls.Add(this.emailTB);
            this.userInfoGroup.Location = new System.Drawing.Point(34, 13);
            this.userInfoGroup.Name = "userInfoGroup";
            this.userInfoGroup.Size = new System.Drawing.Size(528, 245);
            this.userInfoGroup.TabIndex = 16;
            this.userInfoGroup.TabStop = false;
            this.userInfoGroup.Text = "User Information";
            // 
            // infoLBL
            // 
            this.infoLBL.AutoSize = true;
            this.infoLBL.Location = new System.Drawing.Point(18, 160);
            this.infoLBL.Name = "infoLBL";
            this.infoLBL.Size = new System.Drawing.Size(389, 51);
            this.infoLBL.TabIndex = 18;
            this.infoLBL.Tag = "";
            this.infoLBL.Text = "* Indicates a required field, however the truth is not required.\nFeel free to mak" +
    "e something up.\nNote that this information may be displayed publicly.";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(351, 71);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(13, 17);
            this.label2.TabIndex = 17;
            this.label2.Tag = "";
            this.label2.Text = "*";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(351, 40);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(13, 17);
            this.label1.TabIndex = 16;
            this.label1.Tag = "";
            this.label1.Text = "*";
            // 
            // FormSave
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(789, 408);
            this.Controls.Add(this.userInfoGroup);
            this.Controls.Add(this.cancelBTN);
            this.Controls.Add(this.nextBTN);
            this.Controls.Add(this.takePictureBTN);
            this.Controls.Add(this.userImagePB);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "FormSave";
            this.Text = "Create New Model";
            ((System.ComponentModel.ISupportInitialize)(this.userImagePB)).EndInit();
            this.genderRBGroup.ResumeLayout(false);
            this.genderRBGroup.PerformLayout();
            this.userInfoGroup.ResumeLayout(false);
            this.userInfoGroup.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label labelFirstName;
        private System.Windows.Forms.Label labelEmail;
        private System.Windows.Forms.TextBox firstNameTB;
        private System.Windows.Forms.TextBox emailTB;
        private System.Windows.Forms.PictureBox userImagePB;
        private System.Windows.Forms.Button takePictureBTN;
        private System.Windows.Forms.Button nextBTN;
        private System.Windows.Forms.Button cancelBTN;
        private System.Windows.Forms.Label labelLastName;
        private System.Windows.Forms.TextBox lastNameTB;
        private System.Windows.Forms.RadioButton maleRB;
        private System.Windows.Forms.RadioButton femaleRB;
        private System.Windows.Forms.GroupBox genderRBGroup;
        private System.Windows.Forms.GroupBox userInfoGroup;
        private System.Windows.Forms.Label infoLBL;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
    }
}