using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NetSDKSample;
using NetSDK;                         //network SDK（C# version)
using System.Runtime.InteropServices;
using Utility;

namespace SDKAlarmAndUserManage
{
    public partial class frm_Main : Form
    {
        /// <summary>
        /// device handles user login
        /// </summary>
        private int pLoginID;

        /// <summary>
        /// program news tips Title
        /// </summary>
        private const string pMsgTitle = "Network SDK Demo program";

        /// <summary>
        /// finally operating information display format
        /// </summary>
        private const string pErrInfoFormatStyle = "Code:errcode;\ndescription:errmSG.";

        /// <summary>
        /// user information
        /// </summary>
        private USER_MANAGE_INFO userManageInfo;

        /// <summary>
        /// general alarm information
        /// </summary>
        private NET_CLIENT_STATE clientState;

        /// <summary>
        /// occlusion alarm information
        /// </summary>
        private byte[] AlarmShelter;

        /// <summary>
        /// audio alarm information
        /// </summary>
        private byte[] AlarmAudio;

        /// <summary>
        /// external alarm information
        /// </summary>
        private byte[] AlarmExternal;

        /// <summary>
        /// Hard disk damaged alarm information
        /// </summary>
        private byte[] AlarmDiskErr;

        /// <summary>
        /// hard disk insufficient space alarm information
        /// </summary>
        private bool AlarmDiskFull;

        /// <summary>
        /// callback information type
        /// </summary>
        private CALLBACK_TYPE cbkType;

        /// <summary>
        /// obtain configuration information callback
        /// </summary>
        private fMessCallBack msgCallBack;

        /// <summary>
        /// disconnect the device's callback
        /// </summary>
        private fDisConnect disConnect;

        /// <summary>
        /// current user group ID
        /// </summary>
        private uint ActiveGroupID;

        /// <summary>
        /// current user group number Index
        /// </summary>
        private uint ActiveGroupIndex;

        /// <summary>
        /// current user ID
        /// </summary>
        private uint ActiveUserID;

        /// <summary>
        /// current user numberIndex
        /// </summary>
        private uint ActiveUserIndex;

        /// <summary>
        /// permission list items
        /// </summary>
        private struct LISTITEM
        {
            public uint index;
            public uint keyID;
        }
        /// <summary>
        /// permission list index and Key value
        /// </summary>
        private LISTITEM[] rightListArray;

        /// <summary>
        /// user ID list
        /// </summary>
        private uint[] userIDListArray;

        public frm_Main()
        {
            InitializeComponent();
        }

        /// <summary>
        /// device user login/cancellation deal
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnUserLogin_Click(object sender, EventArgs e)
        {
            string strLogin  = StringUtil.ConvertString("Device user login");
            string strLogout = StringUtil.ConvertString("Device user logout");

            if (btnUserLogin.Text.Equals(strLogin))
            {
                frm_AddDevice fLogin = new frm_AddDevice();
                fLogin.ShowDialog();
                if (fLogin.blnOKEnter == true)
                {
                    //device user information obtained
                    NET_DEVICEINFO deviceInfo = new NET_DEVICEINFO();

                    int error = 0;
                    //device user login
                    pLoginID = NETClient.NETLogin(fLogin.cmbDevIP.Text.ToString(), ushort.Parse(fLogin.txtDevProt.Text.ToString()), fLogin.txtName.Text.ToString(), fLogin.txtPassword.Text.ToString(), out deviceInfo, out error);
                    if (pLoginID != 0)
                    {
                        btnUserLogin.BackColor = Color.Yellow;
                        btnUserLogin.Text = strLogout;
                        grpMain.Enabled = true;
                        //read user information
                        GetUserInfo(pLoginID, ref userManageInfo, 3000);
                        //set the information callback function
                        NETClient.NETSetDVRMessCallBack(msgCallBack, IntPtr.Zero);
                        IntPtr pVer = new IntPtr();
                        pVer = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(int)));
                        int nRet = 0;
                        int nVer = 0;
                        bool bRet = NETClient.NETQueryDevState((int)pLoginID, (int)NETClient.NET_DEVSTATE_PROTOCAL_VER, pVer, 4, ref nRet, 2000);
                        if (bRet)
                        {
                             nVer = (int)Marshal.PtrToStructure((IntPtr)((UInt32)pVer), typeof(int));

                             //begin to monitor
                             if (nVer >= 5)
                             {
                                 if (NETClient.NETStartListenEx(pLoginID) == true)
                                 {
                                     timeDisplayAlarmInfo.Enabled = true;
                                 }
                                 else
                                 {
                                     timeDisplayAlarmInfo.Enabled = false;
                                 }
                             }
                             else
                             {
                                 if (NETClient.NETStartListen(pLoginID) == true)
                                 {
                                     timeDisplayAlarmInfo.Enabled = true;
                                 }
                                 else
                                 {
                                     timeDisplayAlarmInfo.Enabled = false;
                                 }
                             }
                        }
                        
                    }
                }
            }
            else if (btnUserLogin.Text.Equals(strLogout))
            {
                bool result = NETClient.NETLogout(pLoginID);
                if (result == false)
                {
                    //report the last operation's error information
                    MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                }


                //screen initialization
                timeDisplayAlarmInfo.Enabled = false;
                this.Controls.Clear();
                InitializeComponent();
                StringUtil.InitControlText(this);
                pLoginID = 0;
                userManageInfo = new USER_MANAGE_INFO();
                clientState = new NET_CLIENT_STATE();
                AlarmAudio = new byte[16];
                AlarmDiskErr = new byte[32];//DVR can load at most 32 hard disk,each one represents a hard disk status. 0:hard disk status is normal;1:hard disk error
                AlarmDiskFull = false;
                AlarmShelter = new byte[16];
                AlarmExternal = new byte[16];
                ActiveUserID = 0;
                ActiveGroupID = 0;
                ActiveGroupIndex = 0;
                ActiveUserIndex = 0;
                btnUserLogin.BackColor = Color.Transparent;
                btnUserLogin.Text = strLogin;
                grpMain.Enabled = false;
                this.WindowState = FormWindowState.Normal;
            }

        }
        /// <summary>
        /// obtain user information 
        /// </summary>
        /// <param name="loginId">login ID</param>
        /// <param name="usrInfo">user information</param>
        /// <param name="waitTime">timeout limit</param>
        private void GetUserInfo(int loginId,ref USER_MANAGE_INFO usrInfo,int waitTime)
        {
             bool blnGetUserInfo = false;
             ActiveUserID = 0;
             ActiveGroupID = 0;
             ActiveGroupIndex = 0;
             ActiveUserIndex = 0;
            //read user information
            blnGetUserInfo = NETClient.NETQueryUserInfo(loginId, ref  usrInfo, waitTime);
            if (blnGetUserInfo == true)
            {
                trvUserManageList.Nodes.Clear();
                chkRightList.Items.Clear();
                //add user group
                foreach (USER_GROUP_INFO gp in userManageInfo.groupList)
                {
                    if (gp.dwID != 0)
                    {
                        trvUserManageList.Nodes.Add(gp.dwID.ToString(), NETClient.NETByteArrayToString(gp.name));
                    }

                }
                //add a user to a user group's Node
                userIDListArray = new uint[200];//Up to 200 users
                uint userIndex = 0;
                foreach (USER_INFO user in userManageInfo.userList)
                {
                    if (user.dwGroupID != 0 && user.dwID != 0)
                    {
                        userIDListArray[userIndex] = user.dwID;
                        trvUserManageList.Nodes[user.dwGroupID.ToString()].Nodes.Add(userIndex.ToString(), NETClient.NETByteArrayToString(user.name));
                        userIndex += 1;
                    }
                }
                //permission list[when there is no group or user to choose,it shows all available permissions]
                chkRightList.Items.Clear();//empty all the permission lists
                rightListArray = new LISTITEM[userManageInfo.dwRightNum];
                for (uint i = 0; i < userManageInfo.dwRightNum; i++)
                {
                    rightListArray[i].index = i;//save the permission list item's index
                    rightListArray[i].keyID = userManageInfo.rightList[i].dwID;//save the permission list item's k value
                    chkRightList.Items.Add(NETClient.NETByteArrayToString(userManageInfo.rightList[i].name), CheckState.Checked);
                }
            }
            else
            {
                MessageBox.Show("failed to get user information!", pMsgTitle);
            }
        }
        /// <summary>
        /// screen load initialization processing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frm_Main_Load(object sender, EventArgs e)
        {
            msgCallBack = new fMessCallBack(GetAlarmMessage);
            disConnect = new fDisConnect(DisConnectEvent);
            AlarmAudio = new byte[16];
            AlarmDiskErr = new byte[32];//DVR can load at most 32 hard disk,each one represents a hard disk status.0:hard disk status is normal;1:hard disk error
            AlarmDiskFull = false;
            AlarmShelter = new byte[16];
            AlarmExternal = new byte[16];
            NETClient.NETInit(disConnect, IntPtr.Zero);
            NETClient.NETSetEncoding(LANGUAGE_ENCODING.gb2312);//character encoding format settings,the default is gb2312 character encoding. If it's other character encoding, please set character encoding format.

            StringUtil.InitControlText(this);
        }
        /// <summary>
        /// screen processing,[all]press button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnFull_Click(object sender, EventArgs e)
        {
            setCheckList(true);            
        }
        /// <summary>
        /// options processing
        /// </summary>
        /// <param name="checkValue"></param>
        private void setCheckList(bool checkValue)
        {
            for (int i = 0; i < chkRightList.Items.Count;i++ )
            {
                chkRightList.SetItemChecked(i, checkValue);
            }
        }

        /// <summary>
        /// screen processing,[clean up]press button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnClear_Click(object sender, EventArgs e)
        {
            setCheckList(false);
        }

        /// <summary>
        /// user selects to process
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void trvUserManageList_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (e.Node.Level == 0)//user group is selected
            {
                setCheckList(false);
                ShowGroupInfo(userManageInfo.groupList[e.Node.Index],true);
                txtUserAddDemo.Text = "";
                txtUserAddName.Text = "";
                txtUserAddPassword.Text = "";
                chkUserReusable.Checked = false;
                //grpUserAdd.Enabled = false;
                ActiveUserID = 0;
                ActiveGroupIndex = (uint)e.Node.Index;
                ActiveUserIndex = 0;
            }
            else//user group is selected
            {
                ShowGroupInfo(userManageInfo.groupList[e.Node.Parent.Index],false);
                setCheckList(false);                
                ShowUserInfo(userManageInfo.userList[int.Parse(e.Node.Name)],true);
                ActiveGroupIndex = (uint)e.Node.Parent.Index;
                ActiveUserIndex = uint.Parse(e.Node.Name);
                grpUserAdd.Enabled = true;
                
            }
        }

        /// <summary>
        /// display user information
        /// </summary>
        /// <param name="userInfo">user information</param>
        /// <param name="blnShowRights">whether to display the permission information</param>
        private void ShowUserInfo(USER_INFO userInfo,bool blnShowRights)
        {
            txtUserAddName.Text = NETClient.NETByteArrayToString(userInfo.name);
            txtUserAddName.ReadOnly = true;
            txtUserAddPassword.Text = NETClient.NETByteArrayToString(userInfo.passWord);
            txtUserAddPassword.ReadOnly = true;
            txtUserAddDemo.Text = NETClient.NETByteArrayToString(userInfo.memo);
            txtUserAddDemo.ReadOnly = true;
            chkUserReusable.Checked=(userInfo.dwReusable ==1?true:false);
            chkUserReusable.AutoCheck =  false;
            ActiveUserID = userInfo.dwID;
            ActiveGroupID = userInfo.dwGroupID;
            if (blnShowRights == true)
            {
                ShowRights(userInfo.rights, userInfo.dwRightNum);
            }
        }
        /// <summary>
        /// display group information
        /// </summary>
        /// <param name="groupInfo">group information</param>
        /// <param name="blnShowRights">whether to display the permission information</param>
        private void ShowGroupInfo(USER_GROUP_INFO groupInfo, bool blnShowRights)
        {
            ActiveGroupID = groupInfo.dwID;
            txtGroupdemo.Text = NETClient.NETByteArrayToString(groupInfo.memo);
            txtGroupdemo.ReadOnly = true;
            txtGroupName.ReadOnly = true;
            txtGroupName.Text = NETClient.NETByteArrayToString(groupInfo.name);
            if (blnShowRights == true)
            {
                ShowRights(groupInfo.rights, groupInfo.dwRightNum);
            }
        }
        /// <summary>
        /// display permission information
        /// </summary>
        /// <param name="rights">permission information list</param>
        /// <param name="rightsNum">permission number</param>
        private void ShowRights(uint[] rights,uint rightsNum)
        {
            
            for (uint i = 0; i < rightsNum; i++)
            {
                foreach (LISTITEM rt in rightListArray)
                {
                    if (rt.keyID == rights[i])
                    {
                        chkRightList.SetItemChecked((int)rt.index, true);
                    }
                }
            }

        }
        /// <summary>
        /// add saving user
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnAddUser_Click(object sender, EventArgs e)
        {
            if (ActiveGroupID != 0)
            {
                switch (btnAddUser.Text)
                {
                    case "Add user":
                        ActiveUserID = 0;
                        grpUserChangePassword.Visible = false;//change user's password controls not to be displayed
                        txtUserAddDemo.Text = "";
                        txtUserAddName.Text = "";
                        txtUserAddPassword.Text = "";
                        chkUserReusable.AutoCheck = true;
                        chkUserReusable.Checked = false;
                        txtUserAddDemo.ReadOnly = false;
                        txtUserAddName.ReadOnly = false;
                        txtUserAddPassword.ReadOnly = false;
                        btnAddUser.BackColor = Color.Yellow;
                        btnAddUser.Text = "Save adding";
                        break;
                    case "Save adding":
                        bool blnAddUser = false;
                        #region << add user's information codes >>
                        //save user's information
                        USER_INFO usrInfo = new USER_INFO("invalid parameter");//these codes are necessary to specify the size of the array allocation,just like passWord,name,meno,rights
                        usrInfo.dwGroupID = userManageInfo.groupList[ActiveGroupIndex].dwID;
                        usrInfo.dwReusable = (uint)(chkUserReusable.Checked == true ? 1 : 0);
                        NETClient.NETStringToByteArry(txtUserAddPassword.Text, ref usrInfo.passWord);
                        NETClient.NETStringToByteArry(txtUserAddName.Text, ref usrInfo.name);
                        NETClient.NETStringToByteArry(txtUserAddDemo.Text, ref usrInfo.memo);
                        //usrInfo.rights = new uint[100];
                        uint rightsNum = 0;
                        for (int i = 0; i < chkRightList.Items.Count; i++)
                        {
                            if (chkRightList.GetItemChecked(i) == true)
                            {
                                usrInfo.rights[rightsNum] = rightListArray[i].keyID;
                                rightsNum += 1;
                            }
                        }
                        usrInfo.dwRightNum = rightsNum;
                        blnAddUser = NETClient.NETOperateUserInfo(pLoginID, USER_OPERATE.NET_USER_ADD, usrInfo, 3000);
                        #endregion
                        if (blnAddUser == false)//success to add user's information                        
                        {
                            MessageBox.Show("failed to save user's information!\n"  +NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                        }
                        GetUserInfo(pLoginID, ref userManageInfo, 3000);
                        btnAddUser.BackColor = Color.Transparent;
                        txtUserAddDemo.Text = "";
                        txtUserAddName.Text = "";
                        txtUserAddPassword.Text = "";
                        chkUserReusable.Checked = false;
                        btnAddUser.Text = "Add user";
                        break;
                }
            }
            else
            {
                MessageBox.Show("please select one group", pMsgTitle);
            }
        }
        /// <summary>
        /// modify user's information
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnEditUser_Click(object sender, EventArgs e)
        {
            if (ActiveUserID != 0)
            {
                switch (btnEditUser.Text)
                {
                    case "Modify user":
                        grpUserChangePassword.Visible = false;//change user's password controls not to be displayed
                        chkUserReusable.AutoCheck = true;
                        txtUserAddDemo.ReadOnly = false;
                        txtUserAddName.ReadOnly = false;
                        txtUserAddPassword.ReadOnly = true;
                        btnEditUser.BackColor = Color.Yellow;
                        btnEditUser.Text = "Save modify";
                        break;
                    case "Save modify":
                        bool blnEditUser = false;
                        #region << save modified user's information codes >>
                        //save modified user's information
                        USER_INFO usrInfo = new USER_INFO("invalided parameter");
                        usrInfo.dwGroupID = userManageInfo.userList[ActiveUserIndex].dwGroupID;
                        usrInfo.dwID = userManageInfo.userList[ActiveUserIndex].dwID;
                        usrInfo.dwReusable = (uint)(chkUserReusable.Checked == true ? 1 : 0);
                        usrInfo.passWord = userManageInfo.userList[ActiveUserIndex].passWord;
                        NETClient.NETStringToByteArry(txtUserAddName.Text, ref usrInfo.name);
                        NETClient.NETStringToByteArry(txtUserAddDemo.Text, ref  usrInfo.memo);
                        //usrInfo.rights = new uint[100];
                        uint rightsNum = 0;
                        for (int i = 0; i < chkRightList.Items.Count; i++)
                        {
                            if (chkRightList.GetItemChecked(i) == true)
                            {
                                usrInfo.rights[rightsNum] = rightListArray[i].keyID;
                                rightsNum += 1;
                            }
                        }
                        usrInfo.dwRightNum = rightsNum;
                        blnEditUser = NETClient.NETOperateUserInfo(pLoginID, USER_OPERATE.NET_USER_EDIT, usrInfo, userManageInfo.userList[ActiveUserIndex], 3000);
                        #endregion
                        if (blnEditUser == true)//success to add user's information
                        {                            
                            GetUserInfo(pLoginID, ref userManageInfo, 3000);
                        }
                        else
                        {
                            MessageBox.Show("failed to modify user's information!\n" + NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                        }
                        btnEditUser.BackColor = Color.Transparent;
                        txtUserAddDemo.Text = "";
                        txtUserAddName.Text = "";
                        txtUserAddPassword.Text = "";
                        chkUserReusable.Checked = false;
                        btnEditUser.Text = "Modify user";
                        ActiveUserID = 0;
                        break;
                }
            }
        }
        /// <summary>
        /// delete users
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDelUser_Click(object sender, EventArgs e)
        {
            bool blnDelUser = false;
            if (ActiveUserID == 0)
            {
                MessageBox.Show("please choose a user name",pMsgTitle);
                return;
            }
            if (MessageBox.Show("confirm to delete the user?", pMsgTitle, MessageBoxButtons.OKCancel, MessageBoxIcon.Warning) == DialogResult.OK)
            { 
                //delete user's codes
                blnDelUser= NETClient.NETOperateUserInfo(pLoginID, USER_OPERATE.NET_USER_DELETE,userManageInfo.userList[ActiveUserIndex], 3000);
                if (blnDelUser == false)
                {
                    MessageBox.Show("failed to delete the!\n" + NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                }
                ActiveUserID = 0;
                GetUserInfo(pLoginID, ref userManageInfo, 3000);
            }
        }
         /// <summary>
         /// modify password and press button
         /// </summary>
         /// <param name="sender"></param>
         /// <param name="e"></param>
        private void btnChangePassword_Click(object sender, EventArgs e)
        {
            if (ActiveUserID != 0)
            {
                switch (btnChangePassword.Text)
                {
                    case "Modify password":
                        grpUserChangePassword.Visible = true;
                        txtUserCNewPassword.Text = "";
                        txtUserNewPassword.Text = "";
                        txtUserOldPassword.Text = "";
                        btnChangePassword.Text = "Save modify";
                        btnChangePassword.BackColor = Color.Yellow;
                        break;
                    case "Save modify":
                        bool blnChangePassword = false;
                        if (txtUserCNewPassword.Text.Equals(txtUserNewPassword.Text) == false)
                        {
                            MessageBox.Show("new password is different from confirmed input password!please input password again", pMsgTitle);
                            txtUserNewPassword.Text = "";
                            txtUserCNewPassword.Text = "";
                            return;
                        }
                        //save modification user's information
                        USER_INFO userNewInfo = new USER_INFO("useless parameter");
                        NETClient.NETStringToByteArry(txtUserNewPassword.Text, ref userNewInfo.passWord);
                        USER_INFO userOldInfo = new USER_INFO("useless parameter");
                        userOldInfo.name = userManageInfo.userList[ActiveUserIndex].name;
                        NETClient.NETStringToByteArry(txtUserOldPassword.Text,ref  userOldInfo.passWord);
                        blnChangePassword = NETClient.NETOperateUserInfo(pLoginID, USER_OPERATE.NET_USER_CHANGEPASSWORD, userNewInfo,userOldInfo, 3000);
                        if (blnChangePassword == false)
                        {
                            MessageBox.Show("failed to modify password!\n"+NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                        }
                        btnChangePassword.Text = "Modify password";
                        btnChangePassword.BackColor = Color.Transparent;
                        break;

                }
            }
            else
            {
                MessageBox.Show("Please choose a user!", pMsgTitle);
            }

        }
        /// <summary>
        /// add a group
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnAddGroup_Click(object sender, EventArgs e)
        {
            switch (btnAddGroup.Text)
            { 
                case "Add group":
                    ActiveGroupID = 0;
                    ActiveGroupIndex = 0;
                    txtGroupName.Text = "";
                    txtGroupName.ReadOnly = false;
                    txtGroupdemo.Text = "";
                    txtGroupdemo.ReadOnly = false;
                    btnAddGroup.Text = "Save group";
                    btnAddGroup.BackColor = Color.Yellow;
                    break;
                case "Save group":
                    bool blnAddGroup = false;

                    USER_GROUP_INFO groupInfo = new USER_GROUP_INFO("useless parameter");
                    NETClient.NETStringToByteArry(txtGroupName.Text,ref  groupInfo.name);
                    NETClient.NETStringToByteArry(txtGroupdemo.Text, ref groupInfo.memo);
                    uint rightsNum = 0;
                    for (int i = 0; i < chkRightList.Items.Count; i++)
                    {
                        if (chkRightList.GetItemChecked(i) == true)
                        {
                            groupInfo.rights[rightsNum] = rightListArray[i].keyID;
                            rightsNum += 1;
                        }
                    }
                    groupInfo.dwRightNum = rightsNum;
                    blnAddGroup = NETClient.NETOperateUserInfo(pLoginID, USER_OPERATE.NET_GROUP_ADD, groupInfo, 3000);
                    if (blnAddGroup == false)
                    {
                        MessageBox.Show("failed to add a group!\n" + NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                    }
                    btnAddGroup.Text = "Add group";
                    btnAddGroup.BackColor = Color.Transparent;
                    ActiveUserID = 0;
                    GetUserInfo(pLoginID, ref userManageInfo, 3000);
                    break;
            }
        }
        /// <summary>
        /// delete a user's group
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDelGroup_Click(object sender, EventArgs e)
        {
            bool blnDelGroup = false;
            if (ActiveGroupID == 0)
            {
                MessageBox.Show("please choose a user's group!", pMsgTitle);
                return;
            }
            if (MessageBox.Show("confirm to delete this user's group?", pMsgTitle, MessageBoxButtons.OKCancel, MessageBoxIcon.Warning) == DialogResult.OK)
            {
                //delete user's codes
                blnDelGroup=NETClient.NETOperateUserInfo(pLoginID, USER_OPERATE.NET_GROUP_DELETE, userManageInfo.groupList[ActiveGroupIndex], 3000);
                if (blnDelGroup == false)
                {
                    MessageBox.Show("failed to delete group!\n" + NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                }
                ActiveGroupID = 0;
                GetUserInfo(pLoginID, ref userManageInfo, 3000);
            }
        }
        /// <summary>
        /// modify a user's group
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnEditGroup_Click(object sender, EventArgs e)
        {
            if (ActiveGroupID == 0)
            {
                MessageBox.Show("please choose a user's group!", pMsgTitle);
                return;
            }
            switch (btnEditGroup.Text)
            { 
                case "Modify group":
                    txtGroupName.ReadOnly = false;
                    txtGroupdemo.ReadOnly = false;
                    btnEditGroup.Text = "Save group";
                    btnEditGroup.BackColor = Color.Yellow;
                    break;
                case "Save group":
                    bool blnAddGroup = false;
                    USER_GROUP_INFO groupInfo = new USER_GROUP_INFO("useless parameter");
                    groupInfo.dwID = userManageInfo.groupList[ActiveGroupIndex].dwID;                    
                    NETClient.NETStringToByteArry(txtGroupName.Text, ref  groupInfo.name);
                    NETClient.NETStringToByteArry(txtGroupdemo.Text, ref groupInfo.memo);
                    uint rightsNum = 0;
                    for (int i = 0; i < chkRightList.Items.Count; i++)
                    {
                        if (chkRightList.GetItemChecked(i) == true)
                        {
                            groupInfo.rights[rightsNum] = rightListArray[i].keyID;
                            rightsNum += 1;
                        }
                    }
                    groupInfo.dwRightNum = rightsNum;
                    blnAddGroup = NETClient.NETOperateUserInfo(pLoginID, USER_OPERATE.NET_GROUP_EDIT, groupInfo, userManageInfo.groupList[ActiveGroupIndex], 3000);
                    if (blnAddGroup == false)
                    {
                        MessageBox.Show("failed to modify a group!\n" + NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                       
                    }
                    btnEditGroup.Text = "Modify group";
                    btnEditGroup.BackColor = Color.Transparent;
                    ActiveUserID = 0;
                    GetUserInfo(pLoginID, ref userManageInfo, 3000);
                    break;
            }
        }
        /// <summary>
        ///  deal with alarm information
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timeDisplayAlarmInfo_Tick(object sender, EventArgs e)
        {
            //display alarm information
            switch (cbkType)
            {
                case CALLBACK_TYPE.NET_COMM_ALARM://display general alarm information
                    SetAlarmControlEnable(clientState.channelcount);
                    #region << input alarm >>
                    chkAlarmIn00.Checked = (clientState.alarm[0] == 1 && chkAlarmIn00.Enabled == true ? true : false);
                    chkAlarmIn01.Checked = (clientState.alarm[1] == 1 && chkAlarmIn01.Enabled == true ? true : false);
                    chkAlarmIn02.Checked = (clientState.alarm[2] == 1 && chkAlarmIn02.Enabled == true ? true : false);
                    chkAlarmIn03.Checked = (clientState.alarm[3] == 1 && chkAlarmIn03.Enabled == true ? true : false);
                    chkAlarmIn04.Checked = (clientState.alarm[4] == 1 && chkAlarmIn04.Enabled == true ? true : false);
                    chkAlarmIn05.Checked = (clientState.alarm[5] == 1 && chkAlarmIn05.Enabled == true ? true : false);
                    chkAlarmIn06.Checked = (clientState.alarm[6] == 1 && chkAlarmIn06.Enabled == true ? true : false);
                    chkAlarmIn07.Checked = (clientState.alarm[7] == 1 && chkAlarmIn07.Enabled == true ? true : false);
                    chkAlarmIn08.Checked = (clientState.alarm[8] == 1 && chkAlarmIn08.Enabled == true ? true : false);
                    chkAlarmIn09.Checked = (clientState.alarm[9] == 1 && chkAlarmIn09.Enabled == true ? true : false);
                    chkAlarmIn10.Checked = (clientState.alarm[10] == 1 && chkAlarmIn10.Enabled == true ? true : false);
                    chkAlarmIn11.Checked = (clientState.alarm[11] == 1 && chkAlarmIn11.Enabled == true ? true : false);
                    chkAlarmIn12.Checked = (clientState.alarm[12] == 1 && chkAlarmIn12.Enabled == true ? true : false);
                    chkAlarmIn13.Checked = (clientState.alarm[13] == 1 && chkAlarmIn13.Enabled == true ? true : false);
                    chkAlarmIn14.Checked = (clientState.alarm[14] == 1 && chkAlarmIn14.Enabled == true ? true : false);
                    chkAlarmIn15.Checked = (clientState.alarm[15] == 1 && chkAlarmIn15.Enabled == true ? true : false);
                    #endregion
                    #region << motion detection >>
                    chkMotionDetect00.Checked = (clientState.motiondection[0] == 1 && chkMotionDetect00.Enabled == true ? true : false);
                    chkMotionDetect01.Checked = (clientState.motiondection[1] == 1 && chkMotionDetect01.Enabled == true ? true : false);
                    chkMotionDetect02.Checked = (clientState.motiondection[2] == 1 && chkMotionDetect02.Enabled == true ? true : false);
                    chkMotionDetect03.Checked = (clientState.motiondection[3] == 1 && chkMotionDetect03.Enabled == true ? true : false);
                    chkMotionDetect04.Checked = (clientState.motiondection[4] == 1 && chkMotionDetect04.Enabled == true ? true : false);
                    chkMotionDetect05.Checked = (clientState.motiondection[5] == 1 && chkMotionDetect05.Enabled == true ? true : false);
                    chkMotionDetect06.Checked = (clientState.motiondection[6] == 1 && chkMotionDetect06.Enabled == true ? true : false);
                    chkMotionDetect07.Checked = (clientState.motiondection[7] == 1 && chkMotionDetect07.Enabled == true ? true : false);
                    chkMotionDetect08.Checked = (clientState.motiondection[8] == 1 && chkMotionDetect08.Enabled == true ? true : false);
                    chkMotionDetect09.Checked = (clientState.motiondection[9] == 1 && chkMotionDetect09.Enabled == true ? true : false);
                    chkMotionDetect10.Checked = (clientState.motiondection[10] == 1 && chkMotionDetect10.Enabled == true ? true : false);
                    chkMotionDetect11.Checked = (clientState.motiondection[11] == 1 && chkMotionDetect11.Enabled == true ? true : false);
                    chkMotionDetect12.Checked = (clientState.motiondection[12] == 1 && chkMotionDetect12.Enabled == true ? true : false);
                    chkMotionDetect13.Checked = (clientState.motiondection[13] == 1 && chkMotionDetect13.Enabled == true ? true : false);
                    chkMotionDetect14.Checked = (clientState.motiondection[14] == 1 && chkMotionDetect14.Enabled == true ? true : false);
                    chkMotionDetect15.Checked = (clientState.motiondection[15] == 1 && chkMotionDetect15.Enabled == true ? true : false);
                    #endregion
                    #region << video loss >>
                    chkVideoLost00.Checked = (clientState.videolost[0] == 1 && chkVideoLost00.Enabled == true ? true : false);
                    chkVideoLost01.Checked = (clientState.videolost[1] == 1 && chkVideoLost01.Enabled == true ? true : false);
                    chkVideoLost02.Checked = (clientState.videolost[2] == 1 && chkVideoLost02.Enabled == true ? true : false);
                    chkVideoLost03.Checked = (clientState.videolost[3] == 1 && chkVideoLost03.Enabled == true ? true : false);
                    chkVideoLost04.Checked = (clientState.videolost[4] == 1 && chkVideoLost04.Enabled == true ? true : false);
                    chkVideoLost05.Checked = (clientState.videolost[5] == 1 && chkVideoLost05.Enabled == true ? true : false);
                    chkVideoLost06.Checked = (clientState.videolost[6] == 1 && chkVideoLost06.Enabled == true ? true : false);
                    chkVideoLost07.Checked = (clientState.videolost[7] == 1 && chkVideoLost07.Enabled == true ? true : false);
                    chkVideoLost08.Checked = (clientState.videolost[8] == 1 && chkVideoLost08.Enabled == true ? true : false);
                    chkVideoLost09.Checked = (clientState.videolost[9] == 1 && chkVideoLost09.Enabled == true ? true : false);
                    chkVideoLost10.Checked = (clientState.videolost[10] == 1 && chkVideoLost10.Enabled == true ? true : false);
                    chkVideoLost11.Checked = (clientState.videolost[11] == 1 && chkVideoLost11.Enabled == true ? true : false);
                    chkVideoLost12.Checked = (clientState.videolost[12] == 1 && chkVideoLost12.Enabled == true ? true : false);
                    chkVideoLost13.Checked = (clientState.videolost[13] == 1 && chkVideoLost13.Enabled == true ? true : false);
                    chkVideoLost14.Checked = (clientState.videolost[14] == 1 && chkVideoLost14.Enabled == true ? true : false);
                    chkVideoLost15.Checked = (clientState.videolost[15] == 1 && chkVideoLost15.Enabled == true ? true : false);
                    #endregion
                    break;
                case CALLBACK_TYPE.NET_SHELTER_ALARM://video masking alarm
                    #region << video masking alarm >>
                    chkShelter00.Checked = (AlarmShelter[0] == 1 && chkShelter00.Enabled == true ? true : false);
                    chkShelter01.Checked = (AlarmShelter[1] == 1 && chkShelter01.Enabled == true ? true : false);
                    chkShelter02.Checked = (AlarmShelter[2] == 1 && chkShelter02.Enabled == true ? true : false);
                    chkShelter03.Checked = (AlarmShelter[3] == 1 && chkShelter03.Enabled == true ? true : false);
                    chkShelter04.Checked = (AlarmShelter[4] == 1 && chkShelter04.Enabled == true ? true : false);
                    chkShelter05.Checked = (AlarmShelter[5] == 1 && chkShelter05.Enabled == true ? true : false);
                    chkShelter06.Checked = (AlarmShelter[6] == 1 && chkShelter06.Enabled == true ? true : false);
                    chkShelter07.Checked = (AlarmShelter[7] == 1 && chkShelter07.Enabled == true ? true : false);
                    chkShelter08.Checked = (AlarmShelter[8] == 1 && chkShelter08.Enabled == true ? true : false);
                    chkShelter09.Checked = (AlarmShelter[9] == 1 && chkShelter09.Enabled == true ? true : false);
                    chkShelter10.Checked = (AlarmShelter[10] == 1 && chkShelter10.Enabled == true ? true : false);
                    chkShelter11.Checked = (AlarmShelter[11] == 1 && chkShelter11.Enabled == true ? true : false);
                    chkShelter12.Checked = (AlarmShelter[12] == 1 && chkShelter12.Enabled == true ? true : false);
                    chkShelter13.Checked = (AlarmShelter[13] == 1 && chkShelter13.Enabled == true ? true : false);
                    chkShelter14.Checked = (AlarmShelter[14] == 1 && chkShelter14.Enabled == true ? true : false);
                    chkShelter15.Checked = (AlarmShelter[15] == 1 && chkShelter15.Enabled == true ? true : false);
                    #endregion
                    break;
                case CALLBACK_TYPE.NET_DISK_FULL_ALARM://hard disk space isn't enough
                    chkDiskFull.Checked = AlarmDiskFull;
                    break;
                case CALLBACK_TYPE.NET_DISK_ERROR_ALARM://hard disk is damaged
                    #region << hard disk is damaged >>
                    string strTemp="";
                    foreach(byte bt in AlarmDiskErr)
                    {
                        strTemp+=bt.ToString();
                    }
                    labDiskBroken.Text = strTemp;
                    #endregion
                    break;
                case CALLBACK_TYPE.NET_SOUND_DETECT_ALARM://audio alarm
                    #region << audio alarm >>
                    chkAudio00.Checked = (AlarmAudio[0] == 1 && chkAudio00.Enabled == true ? true : false);
                    chkAudio01.Checked = (AlarmAudio[1] == 1 && chkAudio01.Enabled == true ? true : false);
                    chkAudio02.Checked = (AlarmAudio[2] == 1 && chkAudio02.Enabled == true ? true : false);
                    chkAudio03.Checked = (AlarmAudio[3] == 1 && chkAudio03.Enabled == true ? true : false);
                    chkAudio04.Checked = (AlarmAudio[4] == 1 && chkAudio04.Enabled == true ? true : false);
                    chkAudio05.Checked = (AlarmAudio[5] == 1 && chkAudio05.Enabled == true ? true : false);
                    chkAudio06.Checked = (AlarmAudio[6] == 1 && chkAudio06.Enabled == true ? true : false);
                    chkAudio07.Checked = (AlarmAudio[7] == 1 && chkAudio07.Enabled == true ? true : false);
                    chkAudio08.Checked = (AlarmAudio[8] == 1 && chkAudio08.Enabled == true ? true : false);
                    chkAudio09.Checked = (AlarmAudio[9] == 1 && chkAudio09.Enabled == true ? true : false);
                    chkAudio10.Checked = (AlarmAudio[10] == 1 && chkAudio10.Enabled == true ? true : false);
                    chkAudio11.Checked = (AlarmAudio[11] == 1 && chkAudio11.Enabled == true ? true : false);
                    chkAudio12.Checked = (AlarmAudio[12] == 1 && chkAudio12.Enabled == true ? true : false);
                    chkAudio13.Checked = (AlarmAudio[13] == 1 && chkAudio13.Enabled == true ? true : false);
                    chkAudio14.Checked = (AlarmAudio[14] == 1 && chkAudio14.Enabled == true ? true : false);
                    chkAudio15.Checked = (AlarmAudio[15] == 1 && chkAudio15.Enabled == true ? true : false);
                    #endregion                    
                    break;
                case CALLBACK_TYPE.NET_ALARM_ALARM_EX:
                    #region << external alarm >>
                    chkAlarmIn00.Checked = (AlarmExternal[0] == 1 && chkAlarmIn00.Enabled == true ? true : false);
                    chkAlarmIn01.Checked = (AlarmExternal[1] == 1 && chkAlarmIn01.Enabled == true ? true : false);
                    chkAlarmIn02.Checked = (AlarmExternal[2] == 1 && chkAlarmIn02.Enabled == true ? true : false);
                    chkAlarmIn03.Checked = (AlarmExternal[3] == 1 && chkAlarmIn03.Enabled == true ? true : false);
                    chkAlarmIn04.Checked = (AlarmExternal[4] == 1 && chkAlarmIn04.Enabled == true ? true : false);
                    chkAlarmIn05.Checked = (AlarmExternal[5] == 1 && chkAlarmIn05.Enabled == true ? true : false);
                    chkAlarmIn06.Checked = (AlarmExternal[6] == 1 && chkAlarmIn06.Enabled == true ? true : false);
                    chkAlarmIn07.Checked = (AlarmExternal[7] == 1 && chkAlarmIn07.Enabled == true ? true : false);
                    chkAlarmIn08.Checked = (AlarmExternal[8] == 1 && chkAlarmIn08.Enabled == true ? true : false);
                    chkAlarmIn09.Checked = (AlarmExternal[9] == 1 && chkAlarmIn09.Enabled == true ? true : false);
                    chkAlarmIn10.Checked = (AlarmExternal[10] == 1 && chkAlarmIn10.Enabled == true ? true : false);
                    chkAlarmIn11.Checked = (AlarmExternal[11] == 1 && chkAlarmIn11.Enabled == true ? true : false);
                    chkAlarmIn12.Checked = (AlarmExternal[12] == 1 && chkAlarmIn12.Enabled == true ? true : false);
                    chkAlarmIn13.Checked = (AlarmExternal[13] == 1 && chkAlarmIn13.Enabled == true ? true : false);
                    chkAlarmIn14.Checked = (AlarmExternal[14] == 1 && chkAlarmIn14.Enabled == true ? true : false);
                    chkAlarmIn15.Checked = (AlarmExternal[15] == 1 && chkAlarmIn15.Enabled == true ? true : false);
                    #endregion   
                    break;
            }
        }

        /// <summary>
        /// gain alarm information processing
        /// </summary>
        /// <param name="lCommand">command</param>
        /// <param name="lLoginID">login ID</param>
        /// <param name="pBuf">buffer</param>
        /// <param name="dwBufLen">size of the buffer data</param>
        /// <param name="pchDVRIP">DVR device's IP address</param>
        /// <param name="nDVRPort">DVR device's port</param>
        /// <param name="dwUser">user's data</param>
        /// <returns></returns>
        private bool GetAlarmMessage(int lCommand, int lLoginID, IntPtr pBuf, UInt32 dwBufLen, IntPtr pchDVRIP, int nDVRPort, UInt32 dwUser)
        {
            bool returnValue = false;
            //MessageBox.Show("HI1");
            
            switch (lCommand)
            { 
                case (int)CALLBACK_TYPE.NET_COMM_ALARM://general alarm information
                    cbkType = CALLBACK_TYPE.NET_COMM_ALARM;
                    clientState = (NET_CLIENT_STATE)Marshal.PtrToStructure(pBuf, typeof(NET_CLIENT_STATE));
                    #region << testing codes >>
                    
                    #endregion
                    break;
                case (int)CALLBACK_TYPE.NET_SHELTER_ALARM://video masking alarm
                    cbkType = CALLBACK_TYPE.NET_SHELTER_ALARM;
                    for (int i = 0; i < dwBufLen; i++)
                    {
                        AlarmShelter[i] = (byte)Marshal.PtrToStructure((IntPtr)((UInt32)pBuf + i), typeof(byte));
                    }
                    break;
                case (int)CALLBACK_TYPE.NET_DISK_FULL_ALARM://hard disk space isn't enough
                    cbkType = CALLBACK_TYPE.NET_DISK_FULL_ALARM;
                    AlarmDiskFull = (bool)Marshal.PtrToStructure(pBuf, typeof(bool));
                    break;
                case (int)CALLBACK_TYPE.NET_DISK_ERROR_ALARM://hard disk is damaged
                    cbkType = CALLBACK_TYPE.NET_DISK_ERROR_ALARM;
                    for (int i = 0; i < dwBufLen; i++)
                    {
                        AlarmDiskErr[i] = (byte)Marshal.PtrToStructure((IntPtr)((UInt32)pBuf + i), typeof(byte));
                    }
                    break;
                case (int)CALLBACK_TYPE.NET_SOUND_DETECT_ALARM://audio alarm
                    cbkType = CALLBACK_TYPE.NET_SOUND_DETECT_ALARM;
                    for (int i = 0; i < dwBufLen; i++)
                    {
                        AlarmAudio[i] = (byte)Marshal.PtrToStructure((IntPtr)((UInt32)pBuf + i), typeof(byte));
                    }
                    break;
                case (int)CALLBACK_TYPE.NET_ALARM_ALARM_EX://external alarm
                    cbkType = CALLBACK_TYPE.NET_ALARM_ALARM_EX;
                    for (int i = 0; i < dwBufLen; i++)
                    {
                        AlarmExternal[i] = (byte)Marshal.PtrToStructure((IntPtr)((UInt32)pBuf + i), typeof(byte));
                    }
                    break;
            }
            return returnValue;
        }
        /// <summary>
        /// device disconnect equipment processing
        /// </summary>
        /// <param name="lLoginID"></param>
        /// <param name="pchDVRIP"></param>
        /// <param name="nDVRPort"></param>
        /// <param name="dwUser"></param>
        private void DisConnectEvent(int lLoginID, StringBuilder pchDVRIP, int nDVRPort, IntPtr dwUser)
        {
            //device disconnect equipment processing           
            MessageBox.Show("device disconnect",pMsgTitle);
        }
        /// <summary>
        /// set alarm display control interface effective
        /// </summary>
        /// <param name="channelNum">number of channels</param>
        private void SetAlarmControlEnable(int channelNum)
        {
            bool blnEnable = false;
            if (channelNum > 0)
            {
                blnEnable = true;
            }
            chkAlarmIn00.Enabled = blnEnable;
            chkShelter00.Enabled = blnEnable;
            chkMotionDetect00.Enabled = blnEnable;
            chkVideoLost00.Enabled = blnEnable;
            chkAudio00.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 1)
            {
                blnEnable = true;
            }
            chkAlarmIn01.Enabled = blnEnable;
            chkShelter01.Enabled = blnEnable;
            chkMotionDetect01.Enabled = blnEnable;
            chkVideoLost01.Enabled = blnEnable;
            chkAudio01.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 2)
            {
                blnEnable = true;
            }
            chkAlarmIn02.Enabled = blnEnable;
            chkShelter02.Enabled = blnEnable;
            chkMotionDetect02.Enabled = blnEnable;
            chkVideoLost02.Enabled = blnEnable;
            chkAudio02.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 3)
            {
                blnEnable = true;
            }
            chkAlarmIn03.Enabled = blnEnable;
            chkShelter03.Enabled = blnEnable;
            chkMotionDetect03.Enabled = blnEnable;
            chkVideoLost03.Enabled = blnEnable;
            chkAudio03.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 4)
            {
                blnEnable = true;
            }
            chkAlarmIn04.Enabled = blnEnable;
            chkShelter04.Enabled = blnEnable;
            chkMotionDetect04.Enabled = blnEnable;
            chkVideoLost04.Enabled = blnEnable;
            chkAudio04.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 5)
            {
                blnEnable = true;
            }
            chkAlarmIn05.Enabled = blnEnable;
            chkShelter05.Enabled = blnEnable;
            chkMotionDetect05.Enabled = blnEnable;
            chkVideoLost05.Enabled = blnEnable;
            chkAudio05.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 6)
            {
                blnEnable = true;
            }
            chkAlarmIn06.Enabled = blnEnable;
            chkShelter06.Enabled = blnEnable;
            chkMotionDetect06.Enabled = blnEnable;
            chkVideoLost06.Enabled = blnEnable;
            chkAudio06.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 7)
            {
                blnEnable = true;
            }
            chkAlarmIn07.Enabled = blnEnable;
            chkShelter07.Enabled = blnEnable;
            chkMotionDetect07.Enabled = blnEnable;
            chkVideoLost07.Enabled = blnEnable;
            chkAudio07.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 8)
            {
                blnEnable = true;
            }
            chkAlarmIn08.Enabled = blnEnable;
            chkShelter08.Enabled = blnEnable;
            chkMotionDetect08.Enabled = blnEnable;
            chkVideoLost08.Enabled = blnEnable;
            chkAudio08.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 9)
            {
                blnEnable = true;
            }
            chkAlarmIn09.Enabled = blnEnable;
            chkShelter09.Enabled = blnEnable;
            chkMotionDetect09.Enabled = blnEnable;
            chkVideoLost09.Enabled = blnEnable;
            chkAudio09.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 10)
            {
                blnEnable = true;
            }
            chkAlarmIn10.Enabled = blnEnable;
            chkShelter10.Enabled = blnEnable;
            chkMotionDetect10.Enabled = blnEnable;
            chkVideoLost10.Enabled = blnEnable;
            chkAudio10.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 11)
            {
                blnEnable = true;
            }
            chkAlarmIn11.Enabled = blnEnable;
            chkShelter11.Enabled = blnEnable;
            chkMotionDetect11.Enabled = blnEnable;
            chkVideoLost11.Enabled = blnEnable;
            chkAudio11.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 12)
            {
                blnEnable = true;
            }
            chkAlarmIn12.Enabled = blnEnable;
            chkShelter12.Enabled = blnEnable;
            chkMotionDetect12.Enabled = blnEnable;
            chkVideoLost12.Enabled = blnEnable;
            chkAudio12.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 13)
            {
                blnEnable = true;
            }
            chkAlarmIn13.Enabled = blnEnable;
            chkShelter13.Enabled = blnEnable;
            chkMotionDetect13.Enabled = blnEnable;
            chkVideoLost13.Enabled = blnEnable;
            chkAudio13.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 14)
            {
                blnEnable = true;
            }
            chkAlarmIn14.Enabled = blnEnable;
            chkShelter14.Enabled = blnEnable;
            chkMotionDetect14.Enabled = blnEnable;
            chkVideoLost14.Enabled = blnEnable;
            chkAudio14.Enabled = blnEnable;
            blnEnable = false;
            if (channelNum > 15)
            {
                blnEnable = true;
            }
            chkAlarmIn15.Enabled = blnEnable;
            chkShelter15.Enabled = blnEnable;
            chkMotionDetect15.Enabled = blnEnable;
            chkVideoLost15.Enabled = blnEnable;
            chkAudio15.Enabled = blnEnable;
            blnEnable = false;            

        }
    }
}