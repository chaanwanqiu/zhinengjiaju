const app = getApp()

Page({
  data: {
  },

  send3: function () {
    var that = this //创建一个名为that的变量来保存this当前的值  
    wx.request({
      url: 'http://api.heclouds.com/devices/504601808/datapoints?type=3',
      method: 'post',
      data: {
        kongtiao: '3'  //这里是发送给服务器的参数（参数名：参数值）  
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



  },

  send1: function () {
    var that = this //创建一个名为that的变量来保存this当前的值  
    wx.request({
      url: 'http://api.heclouds.com/devices/504601808/datapoints?type=3',
      method: 'post',
      data: {
        kongtiao: '8'  //这里是发送给服务器的参数（参数名：参数值）  
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


    4; setTimeout(function () {
      var that = this //创建一个名为that的变量来保存this当前的值  
      wx.request({
        url: 'http://api.heclouds.com/devices/504601808/datapoints?type=3',
        method: 'post',
        data: {
          kongtiao: '9'  //这里是发送给服务器的参数（参数名：参数值）  
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

  },
  send2: function () {
    var that = this //创建一个名为that的变量来保存this当前的值  
    wx.request({
      url: 'http://api.heclouds.com/devices/504601808/datapoints?type=3',
      method: 'post',
      data: {
        kongtiao: '9'  //这里是发送给服务器的参数（参数名：参数值）  
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


    5; setTimeout(function () {
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

  },
  send3: function () {
    var that = this //创建一个名为that的变量来保存this当前的值  
    wx.request({
      url: 'http://api.heclouds.com/devices/504601808/datapoints?type=3',
      method: 'post',
      data: {
        kongtiao: 'b'  //这里是发送给服务器的参数（参数名：参数值）  
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


    5; setTimeout(function () {
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