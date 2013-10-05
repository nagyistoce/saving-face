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
            this.labelName = new System.Windows.Forms.Label();
            this.labelEmail = new System.Windows.Forms.Label();
            this.textBoxName = new System.Windows.Forms.TextBox();
            this.textBoxEmail = new System.Windows.Forms.TextBox();
            this.buttonScanFace = new System.Windows.Forms.Button();
            this.pictureBoxTakePicture = new System.Windows.Forms.PictureBox();
            this.buttonTakePicture = new System.Windows.Forms.Button();
            this.buttonSave = new System.Windows.Forms.Button();
            this.buttonBack = new System.Windows.Forms.Button();
            this.richTextBoxDebug = new System.Windows.Forms.RichTextBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxTakePicture)).BeginInit();
            this.SuspendLayout();
            // 
            // labelName
            // 
            this.labelName.AutoSize = true;
            this.labelName.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelName.Location = new System.Drawing.Point(13, 13);
            this.labelName.Name = "labelName";
            this.labelName.Size = new System.Drawing.Size(55, 20);
            this.labelName.TabIndex = 0;
            this.labelName.Text = "Name:";
            // 
            // labelEmail
            // 
            this.labelEmail.AutoSize = true;
            this.labelEmail.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelEmail.Location = new System.Drawing.Point(13, 73);
            this.labelEmail.Name = "labelEmail";
            this.labelEmail.Size = new System.Drawing.Size(52, 20);
            this.labelEmail.TabIndex = 1;
            this.labelEmail.Text = "Email:";
            // 
            // textBoxName
            // 
            this.textBoxName.Location = new System.Drawing.Point(84, 13);
            this.textBoxName.Name = "textBoxName";
            this.textBoxName.Size = new System.Drawing.Size(100, 20);
            this.textBoxName.TabIndex = 2;
            // 
            // textBoxEmail
            // 
            this.textBoxEmail.Location = new System.Drawing.Point(84, 73);
            this.textBoxEmail.Name = "textBoxEmail";
            this.textBoxEmail.Size = new System.Drawing.Size(100, 20);
            this.textBoxEmail.TabIndex = 3;
            // 
            // buttonScanFace
            // 
            this.buttonScanFace.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonScanFace.Location = new System.Drawing.Point(17, 172);
            this.buttonScanFace.Name = "buttonScanFace";
            this.buttonScanFace.Size = new System.Drawing.Size(166, 45);
            this.buttonScanFace.TabIndex = 4;
            this.buttonScanFace.Text = "Scan Face";
            this.buttonScanFace.UseVisualStyleBackColor = true;
            // 
            // pictureBoxTakePicture
            // 
            this.pictureBoxTakePicture.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxTakePicture.Image")));
            this.pictureBoxTakePicture.Location = new System.Drawing.Point(214, 13);
            this.pictureBoxTakePicture.Name = "pictureBoxTakePicture";
            this.pictureBoxTakePicture.Size = new System.Drawing.Size(167, 204);
            this.pictureBoxTakePicture.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBoxTakePicture.TabIndex = 5;
            this.pictureBoxTakePicture.TabStop = false;
            // 
            // buttonTakePicture
            // 
            this.buttonTakePicture.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonTakePicture.Location = new System.Drawing.Point(16, 126);
            this.buttonTakePicture.Name = "buttonTakePicture";
            this.buttonTakePicture.Size = new System.Drawing.Size(167, 40);
            this.buttonTakePicture.TabIndex = 6;
            this.buttonTakePicture.Text = "Take Picture";
            this.buttonTakePicture.UseVisualStyleBackColor = true;
            // 
            // buttonSave
            // 
            this.buttonSave.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonSave.Location = new System.Drawing.Point(17, 224);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(179, 154);
            this.buttonSave.TabIndex = 7;
            this.buttonSave.Text = "Save";
            this.buttonSave.UseVisualStyleBackColor = true;
            // 
            // buttonBack
            // 
            this.buttonBack.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonBack.Location = new System.Drawing.Point(202, 224);
            this.buttonBack.Name = "buttonBack";
            this.buttonBack.Size = new System.Drawing.Size(179, 154);
            this.buttonBack.TabIndex = 8;
            this.buttonBack.Text = "Back";
            this.buttonBack.UseVisualStyleBackColor = true;
            this.buttonBack.Click += new System.EventHandler(this.buttonBack_Click);
            // 
            // richTextBoxDebug
            // 
            this.richTextBoxDebug.Location = new System.Drawing.Point(388, 13);
            this.richTextBoxDebug.Name = "richTextBoxDebug";
            this.richTextBoxDebug.Size = new System.Drawing.Size(340, 365);
            this.richTextBoxDebug.TabIndex = 9;
            this.richTextBoxDebug.Text = "";
            // 
            // FormSave
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(740, 390);
            this.Controls.Add(this.richTextBoxDebug);
            this.Controls.Add(this.buttonBack);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.buttonTakePicture);
            this.Controls.Add(this.pictureBoxTakePicture);
            this.Controls.Add(this.buttonScanFace);
            this.Controls.Add(this.textBoxEmail);
            this.Controls.Add(this.textBoxName);
            this.Controls.Add(this.labelEmail);
            this.Controls.Add(this.labelName);
            this.Name = "FormSave";
            this.Text = "FormSave";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxTakePicture)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelName;
        private System.Windows.Forms.Label labelEmail;
        private System.Windows.Forms.TextBox textBoxName;
        private System.Windows.Forms.TextBox textBoxEmail;
        private System.Windows.Forms.Button buttonScanFace;
        private System.Windows.Forms.PictureBox pictureBoxTakePicture;
        private System.Windows.Forms.Button buttonTakePicture;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Button buttonBack;
        private System.Windows.Forms.RichTextBox richTextBoxDebug;
    }
}