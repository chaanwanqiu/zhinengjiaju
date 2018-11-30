const app = getApp()

Page({
  data: {
  },


  onLoad: function () {
    if (!wx.cloud) {
      wx.redirectTo({
        url: '../chooseLib/chooseLib',
      })
      return
    }

    // 获取用户信息
    wx.getSetting({
      success: res => {
        if (res.authSetting['scope.userInfo']) {
          // 已经授权，可以直接调用 getUserInfo 获取头像昵称，不会弹框
          wx.getUserInfo({
            success: res => {
              this.setData({
                avatarUrl: res.userInfo.avatarUrl,
                userInfo: res.userInfo
              })
            }
          })
        }
      }
    })
  },

  onGetUserInfo: function (e) {
    if (!this.logged && e.detail.userInfo) {
      this.setData({
        logged: true,
        avatarUrl: e.detail.userInfo.avatarUrl,
        userInfo: e.detail.userInfo
      })
    }
  },

  onGetOpenid: function () {
    // 调用云函数
    wx.cloud.callFunction({
      name: 'login',
      data: {},
      success: res => {
        console.log('[云函数] [login] user openid: ', res.result.openid)
        app.globalData.openid = res.result.openid
        wx.navigateTo({
          url: '../userConsole/userConsole',
        })
      },
      fail: err => {
        console.error('[云函数] [login] 调用失败', err)
        wx.navigateTo({
          url: '../deployFunctions/deployFunctions',
        })
      }
    })
  },

  // 上传图片
  doUpload: function () {
    // 选择图片
    wx.chooseImage({
      count: 1,
      sizeType: ['compressed'],
      sourceType: ['album', 'camera'],
      success: function (res) {

        wx.showLoading({
          title: '上传中',
        })

        const filePath = res.tempFilePaths[0]

        // 上传图片
        const cloudPath = 'my-image' + filePath.match(/\.[^.]+?$/)[0]
        wx.cloud.uploadFile({
          cloudPath,
          filePath,
          success: res => {
            console.log('[上传文件] 成功：', res)

            app.globalData.fileID = res.fileID
            app.globalData.cloudPath = cloudPath
            app.globalData.imagePath = filePath

            wx.navigateTo({
              url: '../storageConsole/storageConsole'
            })
          },
          fail: e => {
            console.error('[上传文件] 失败：', e)
            wx.showToast({
              icon: 'none',
              title: '上传失败',
            })
          },
          complete: () => {
            wx.hideLoading()
          }
        })

      },
      fail: e => {
        console.error(e)
      }
    })
  },

 send2: function () {
   var that = this //创建一个名为that的变量来保存this当前的值  
   wx.request({
     url: 'http://api.heclouds.com/devices/504601808/datapoints?type=3',
     method: 'post',
     data: {
       kongtiao: '1'  //这里是发送给服务器的参数（参数名：参数值）  
     },
     header: {
       'content-type': 'application/json',
       'api-key': 'imjcKhEeN09X9dxi6T1aqCmPltg='
     },
     success: function (res) {
       that.setData({ //这里是修改data的值  
         test: res.data //test等于服务器返回来的数据  
       });
       console.log(res.data)
     }
   })
 

 1 ;setTimeout( function(){
   var that = this //创建一个名为that的变量来保存this当前的值  
   wx.request({
     url: 'http://api.heclouds.com/devices/504601808/datapoints?type=3',
     method: 'post',
     data: {
       kongtiao: '0'  //这里是发送给服务器的参数（参数名：参数值）  
     },
     header: {
       'content-type': 'application/json',
       'api-key': 'imjcKhEeN09X9dxi6T1aqCmPltg='
     },
     success: function (res) {
       that.setData({ //这里是修改data的值  
         test: res.data //test等于服务器返回来的数据  
       });
       console.log(res.data)
     }
   }) //你需要执行的代码
  }, 6000)

 }
})