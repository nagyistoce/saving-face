namespace SavingFaceGUI
{
    partial class FormMain
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
            this.richTextBoxDebug = new System.Windows.Forms.RichTextBox();
            this.buttonSave = new System.Windows.Forms.Button();
            this.buttonIdentify = new System.Windows.Forms.Button();
            this.buttonExit = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // richTextBoxDebug
            // 
            this.richTextBoxDebug.Location = new System.Drawing.Point(243, 12);
            this.richTextBoxDebug.Name = "richTextBoxDebug";
            this.richTextBoxDebug.Size = new System.Drawing.Size(492, 370);
            this.richTextBoxDebug.TabIndex = 0;
            this.richTextBoxDebug.Text = "";
            // 
            // buttonSave
            // 
            this.buttonSave.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonSave.Location = new System.Drawing.Point(12, 12);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(225, 114);
            this.buttonSave.TabIndex = 1;
            this.buttonSave.Text = "Save";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // buttonIdentify
            // 
            this.buttonIdentify.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonIdentify.Location = new System.Drawing.Point(12, 132);
            this.buttonIdentify.Name = "buttonIdentify";
            this.buttonIdentify.Size = new System.Drawing.Size(225, 124);
            this.buttonIdentify.TabIndex = 2;
            this.buttonIdentify.Text = "Identify";
            this.buttonIdentify.UseVisualStyleBackColor = true;
            this.buttonIdentify.Click += new System.EventHandler(this.buttonIdentify_Click);
            // 
            // buttonExit
            // 
            this.buttonExit.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonExit.Location = new System.Drawing.Point(12, 262);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(225, 120);
            this.buttonExit.TabIndex = 3;
            this.buttonExit.Text = "Exit";
            this.buttonExit.UseVisualStyleBackColor = true;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(747, 394);
            this.Controls.Add(this.buttonExit);
            this.Controls.Add(this.buttonIdentify);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.richTextBoxDebug);
            this.Name = "FormMain";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox richTextBoxDebug;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Button buttonIdentify;
        private System.Windows.Forms.Button buttonExit;
    }
}

