// js
Page({
  data: {
    type: '未知',
    inputVal: '',
    database: { // 数据库内容
      "可回收垃圾": [
        "纸张",
        "塑料瓶",
        "易拉罐",
        "玻璃瓶",
        "报纸"
      ],
      "有害垃圾": [
        "电池",
        "灯管",
        "药品",
        "杀虫剂",
        "化妆品"
      ],
      "厨余垃圾": [
        "果皮",
        "菜叶",
        "剩菜"
      ],
      "其他垃圾": [
        "烟头",
        "尘土",
        "盆栽"
      ]
    }
  },
  onInput: function(e) {
    this.setData({
      inputVal: e.detail.value.trim().toLowerCase()
    })
  },
  navigateToNextPage: function() {
    var value = this.data.inputVal
    var type = '未知'
    for (var key in this.data.database) {
      if (this.data.database[key].indexOf(value) !== -1) {
        type = key
        break
      }
    }
    this.setData({
      type: type
    })
    wx.navigateTo({
      url: '/pages/nextpage/nextpage?type=' + this.data.type
    })
  }
})


