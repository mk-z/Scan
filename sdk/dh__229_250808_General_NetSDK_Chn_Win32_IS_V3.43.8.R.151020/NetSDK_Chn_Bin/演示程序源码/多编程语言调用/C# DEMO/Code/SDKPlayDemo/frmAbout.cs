using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.Reflection;
using PlaySDK;

namespace SDKPlayDemo
{
    partial class frmAbout : Form
    {
        public frmAbout()
        {
            InitializeComponent();

            //  Initialize AboutBox to display the production information included in the assembly
            //  The assembly information settings of application progress can also be changed by this method:
            //  - Project -> Properties -> Applications -> Assembly Information
            //  - AssemblyInfo.cs
            this.Text = String.Format("About {0}", AssemblyTitle);
            this.labelProductName.Text = AssemblyProduct;
            this.labelVersion.Text = String.Format("Version    {0} \nSDKVersion {1}", AssemblyVersion,SDKVersion);
            this.labelCopyright.Text = AssemblyCopyright;
            this.labelCompanyName.Text = AssemblyCompany;
            this.textBoxDescription.Text = AssemblyDescription;
        }

        #region The assembly property accessor

        public string AssemblyTitle
        {
            get
            {
                // Get all Title attributes on this assembly
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyTitleAttribute), false);
                // If at least one Title attribute
                if (attributes.Length > 0)
                {
                    // Please select the first attribute
                    AssemblyTitleAttribute titleAttribute = (AssemblyTitleAttribute)attributes[0];
                    // If the property is non-empty string, it is returned
                    if (titleAttribute.Title != "")
                        return titleAttribute.Title;
                }
                // If there is no Title attribute, or the Title property to an empty string, then return the name of .exe 
                return System.IO.Path.GetFileNameWithoutExtension(Assembly.GetExecutingAssembly().CodeBase);
            }
        }

        public string AssemblyVersion
        {
            get
            {
                return Assembly.GetExecutingAssembly().GetName().Version.ToString();
            }
        }

        public string AssemblyDescription
        {
            get
            {
                // Get all Description attributes of this assembly
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyDescriptionAttribute), false);
                // If the Description property does not exist, it returns an empty string
                if (attributes.Length == 0)
                    return "";
                // If the Description property, the value of the property is returned
                return ((AssemblyDescriptionAttribute)attributes[0]).Description;
            }
        }

        public string AssemblyProduct
        {
            get
            {
                // Get all Product attributes on this assembly
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyProductAttribute), false);
                // If the Product attribute does not exist, it returns an empty string
                if (attributes.Length == 0)
                    return "";
                // If Product attribute value of the property is returned
                return ((AssemblyProductAttribute)attributes[0]).Product;
            }
        }

        public string AssemblyCopyright
        {
            get
            {
                // Get all Copyright attributes on this assembly
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyCopyrightAttribute), false);
                // If the Copyright property does not exist, it returns an empty string
                if (attributes.Length == 0)
                    return "";
                // If there are Copyright property, the value of the property is returned
                return ((AssemblyCopyrightAttribute)attributes[0]).Copyright;
            }
        }

        public string AssemblyCompany
        {
            get
            {
                // Get all Company attributes on this assembly
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyCompanyAttribute), false);
                // If the Company property does not exist, it returns an empty string
                if (attributes.Length == 0)
                    return "";
                // If Company property, the value of the property is returned
                return ((AssemblyCompanyAttribute)attributes[0]).Company;
            }
        }

        public string SDKVersion
        {
            get
            {
                //return Convert.ToString(NETPlay.NETGetSdkVersion());
                return NETPlay.NETGetSdkVersion("A.B.C");
            }
        }
        #endregion

        private void frmAbout_Load(object sender, EventArgs e)
        {
            Utility.StringUtil.InitControlText(this);
        }
    }
}
