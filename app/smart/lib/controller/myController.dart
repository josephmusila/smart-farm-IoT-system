import 'dart:convert';

import 'package:flutter/cupertino.dart';
import 'package:get/get.dart';
import 'package:http/http.dart' as http;
import 'package:smart/model/model.dart';

class MyController {
  Future<Welcome> getData() async {
    var client = http.Client();
    var myData;

    var response = await client.get(Uri.parse(
        "https://api.thingspeak.com/channels/1441178/feeds.json?api_key=VMKANBLHX6UGX9VX&results=1"));
    if (response.statusCode == 200) {
      var jsonString = response.body;
      var jsonMap = json.decode(jsonString);
      debugPrint("daata found");
      debugPrint(jsonString);

      myData = Welcome.fromJson(jsonMap);
    } else {
      debugPrint("error");
      return myData;
    }
    return myData;
  }
}
