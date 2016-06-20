using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace Utility
{
    public sealed class MessageUtil
    {
        public enum MBIconType
        {
            MBIcon_None = 0,
            MBIcon_OK,
            MBIcon_Warning,
            MBIcon_Error
        }

        public enum MBButtonType
        {
            MBBtn_OK = 0,
            MBBtn_OKCancel = 1,
            MBBtn_YesNo = 2,
            MBBtn_YesNoCancel = 3,
            MBBtn_RetryCancel = 4,
            MBBtn_AbortRetryIgnore = 5,
        }

        public static DialogResult ShowMsgBox(string strContent)
        {
            return ShowMsgBox(strContent, string.Empty, MBIconType.MBIcon_None, MBButtonType.MBBtn_OK);
        }

        public static DialogResult ShowMsgBox(string strContent, string strCaption)
        {
            return ShowMsgBox(strContent, strCaption, MBIconType.MBIcon_None, MBButtonType.MBBtn_OK);
        }

        public static DialogResult ShowMsgBox(string strContent, string strCaption, MBIconType iconType)
        {
            return ShowMsgBox(strContent, strCaption, iconType, MBButtonType.MBBtn_OK);
        }

        public static DialogResult ShowMsgBox(string strContent, string strCaption, MBButtonType btnType)
        {
            return ShowMsgBox(strContent, strCaption, MBIconType.MBIcon_None, btnType);
        }

        public static DialogResult ShowMsgBox(string strContent, string strCaption, MBIconType iconType, MBButtonType btnType)
        {
            MsgForm form = new MsgForm();

            form.Content = strContent;
            form.Text = strCaption;
            form.IconType = iconType;
            form.ButtonType = btnType;
            form.AutoSize = true;

            return form.ShowDialog();

        }
    }
}
