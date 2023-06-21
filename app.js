// app.js
App({
  onLaunch: function() {
    // 尝试从本地缓存中读取垃圾分类数据
    var database = wx.getStorageSync('garbage_database')
    if (!database) { // 如果缓存中没有数据，则创建一个默认的数据库
      var defaultDatabase = {
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
      wx.setStorageSync('garbage_database', defaultDatabase)
    }
  }
})

