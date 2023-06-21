// nextpage.js
Page({
  data: {
    type: ''
  },
  onLoad: function(options) {
    var type = options.type || '未知'
    this.setData({
      type: type
    })
  }
})
