import 'dart:async';

import 'package:flutter/material.dart';
import 'package:smart/controller/myController.dart';

import 'model/model.dart';

class HomePage extends StatefulWidget {
  @override
  _HomePageState createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  late Timer timer;
  Future<Welcome>? _welcome;
  @override
  void initState() {
    super.initState();

      _welcome = MyController().getData();

  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Smart Farm Monitoring DashBoard"),
      ),
      body: Container(
        height: 500,
        color: Colors.greenAccent,
        padding: EdgeInsets.all(10),
        margin: EdgeInsets.all(5),
        child: Column(
          children: [
            Container(
              height: 40,
              color: Colors.grey,
              child: Center(
                child: Text(
                  "Latest Update of Received Values",
                  style: TextStyle(
                    fontSize: 20,
                    color: Colors.white,
                  ),
                ),
              ),
            ),
            FutureBuilder<Welcome>(
                future: _welcome,
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
                    return Container(
                      height: 300,
                      child: ListView.builder(
                        itemCount: snapshot.data!.feeds.length,
                        itemBuilder: (context, index) {
                          var mydata = snapshot.data!.feeds[index];
                          return Column(
                            children: [
                              ListTile(
                                leading: Text(
                                  "Last Updated ",
                                  style: TextStyle(
                                    color: Colors.black,
                                    fontSize: 15,
                                  ),
                                ),
                                trailing: Text(
                                  "${mydata.createdAt}",
                                  style: TextStyle(
                                    color: Colors.black,
                                    fontSize: 15,
                                  ),
                                ),
                              ),
                              ListTile(
                                leading: Text(
                                  "Temperature ",
                                  style: TextStyle(
                                    color: Colors.red,
                                    fontSize: 20,
                                  ),
                                ),
                                trailing: Text(
                                  mydata.field1 + " C",
                                  style: TextStyle(
                                    color: Colors.red,
                                    fontSize: 20,
                                  ),
                                ),
                              ),
                              ListTile(
                                leading: Text(
                                  "Humidity ",
                                  style: TextStyle(
                                    color: Colors.red,
                                    fontSize: 20,
                                  ),
                                ),
                                trailing: Text(
                                  mydata.field2 + " %",
                                  style: TextStyle(
                                    color: Colors.red,
                                    fontSize: 20,
                                  ),
                                ),
                              ),
                              ListTile(
                                leading: Text(
                                  "Light Intensity ",
                                  style: TextStyle(
                                    color: Colors.red,
                                    fontSize: 20,
                                  ),
                                ),
                                trailing: Text(
                                  mydata.field3,
                                  style: TextStyle(
                                    color: Colors.red,
                                    fontSize: 20,
                                  ),
                                ),
                              ),
                              ListTile(
                                leading: Text(
                                  "Water Tank Level ",
                                  style: TextStyle(
                                    color: Colors.red,
                                    fontSize: 20,
                                  ),
                                ),
                                trailing: Text(
                                  "",
                                  style: TextStyle(
                                    color: Colors.red,
                                    fontSize: 20,
                                  ),
                                ),
                              ),
                            ],
                          );
                        },
                      ),
                    );
                  } else {
                    return Center(
                      child: CircularProgressIndicator(),
                    );
                  }
                })
          ],
        ),
      ),
    );
  }
}
