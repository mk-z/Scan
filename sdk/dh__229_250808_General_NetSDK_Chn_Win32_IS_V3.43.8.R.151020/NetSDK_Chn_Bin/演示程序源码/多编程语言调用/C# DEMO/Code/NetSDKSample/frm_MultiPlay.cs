using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NetSDK;

namespace NetSDKSample
{
    public partial class frm_MultiPlay : Form
    {
        public bool bOKEnter = false;
        public REALPLAY_TYPE emSplitType = REALPLAY_TYPE.NET_RType_Multiplay_1;
        Dictionary<string, REALPLAY_TYPE> dictSplit;

        public frm_MultiPlay()
        {
            InitializeComponent();
            bOKEnter = false;
            dictSplit = new Dictionary<string, REALPLAY_TYPE>();
            dictSplit.Add("1"    , REALPLAY_TYPE.NET_RType_Multiplay_1);
            dictSplit.Add("4"    , REALPLAY_TYPE.NET_RType_Multiplay_4);
            dictSplit.Add("6"    , REALPLAY_TYPE.NET_RType_Multiplay_6);
            dictSplit.Add("8"    , REALPLAY_TYPE.NET_RType_Multiplay_8);
            dictSplit.Add("9"    , REALPLAY_TYPE.NET_RType_Multiplay_9);
            dictSplit.Add("12"   , REALPLAY_TYPE.NET_RType_Multiplay_12);
            dictSplit.Add("16"   , REALPLAY_TYPE.NET_RType_Multiplay_16);
            dictSplit.Add("25"   , REALPLAY_TYPE.NET_RType_Multiplay_25);        
            dictSplit.Add("36"   , REALPLAY_TYPE.NET_RType_Multiplay_36);
            dictSplit.Add("ALL"  , REALPLAY_TYPE.NET_RType_Multiplay);    
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            bOKEnter = true;
            this.Close();   
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            bOKEnter = false;
            this.Close();
        }

        private void cmbSplitType_SelectedIndexChanged(object sender, EventArgs e)
        {
            string selectItem = (string)this.cmbSplitType.SelectedItem;
            selectItem = selectItem.Trim();

            if (dictSplit.ContainsKey(selectItem))
            {
                emSplitType = dictSplit[selectItem];
            }
        }
    }
}
