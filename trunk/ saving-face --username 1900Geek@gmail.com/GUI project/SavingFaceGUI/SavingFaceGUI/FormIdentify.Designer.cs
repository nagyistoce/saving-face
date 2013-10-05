namespace SavingFaceGUI
{
    partial class FormIdentify
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormIdentify));
            this.pictureBoxFace = new System.Windows.Forms.PictureBox();
            this.richTextBoxIdentification = new System.Windows.Forms.RichTextBox();
            this.richTextBoxDebug = new System.Windows.Forms.RichTextBox();
            this.buttonReidentify = new System.Windows.Forms.Button();
            this.buttonBack = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxFace)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBoxFace
            // 
            this.pictureBoxFace.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxFace.Image")));
            this.pictureBoxFace.Location = new System.Drawing.Point(12, 12);
            this.pictureBoxFace.Name = "pictureBoxFace";
            this.pictureBoxFace.Size = new System.Drawing.Size(195, 208);
            this.pictureBoxFace.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBoxFace.TabIndex = 0;
            this.pictureBoxFace.TabStop = false;
            // 
            // richTextBoxIdentification
            // 
            this.richTextBoxIdentification.Location = new System.Drawing.Point(213, 12);
            this.richTextBoxIdentification.Name = "richTextBoxIdentification";
            this.richTextBoxIdentification.Size = new System.Drawing.Size(202, 208);
            this.richTextBoxIdentification.TabIndex = 1;
            this.richTextBoxIdentification.Text = "";
            // 
            // richTextBoxDebug
            // 
            this.richTextBoxDebug.Location = new System.Drawing.Point(421, 12);
            this.richTextBoxDebug.Name = "richTextBoxDebug";
            this.richTextBoxDebug.Size = new System.Drawing.Size(312, 368);
            this.richTextBoxDebug.TabIndex = 2;
            this.richTextBoxDebug.Text = "";
            // 
            // buttonReidentify
            // 
            this.buttonReidentify.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonReidentify.Location = new System.Drawing.Point(13, 227);
            this.buttonReidentify.Name = "buttonReidentify";
            this.buttonReidentify.Size = new System.Drawing.Size(194, 153);
            this.buttonReidentify.TabIndex = 3;
            this.buttonReidentify.Text = "Reidentify";
            this.buttonReidentify.UseVisualStyleBackColor = true;
            // 
            // buttonBack
            // 
            this.buttonBack.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonBack.Location = new System.Drawing.Point(214, 227);
            this.buttonBack.Name = "buttonBack";
            this.buttonBack.Size = new System.Drawing.Size(201, 153);
            this.buttonBack.TabIndex = 4;
            this.buttonBack.Text = "Back";
            this.buttonBack.UseVisualStyleBackColor = true;
            this.buttonBack.Click += new System.EventHandler(this.buttonBack_Click);
            // 
            // FormIdentify
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(745, 392);
            this.Controls.Add(this.buttonBack);
            this.Controls.Add(this.buttonReidentify);
            this.Controls.Add(this.richTextBoxDebug);
            this.Controls.Add(this.richTextBoxIdentification);
            this.Controls.Add(this.pictureBoxFace);
            this.Name = "FormIdentify";
            this.Text = "FormIdentify";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxFace)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBoxFace;
        private System.Windows.Forms.RichTextBox richTextBoxIdentification;
        private System.Windows.Forms.RichTextBox richTextBoxDebug;
        private System.Windows.Forms.Button buttonReidentify;
        private System.Windows.Forms.Button buttonBack;
    }
}