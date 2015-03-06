create database user_message
use user_message;
Create table Dinner_Table
(
	Table_ID char(3) not null ,
	Seat_Num int  not null,
	Table_Position varchar(20),
	Table_Situation varchar(10)
	Primary key(Table_ID)
); 

insert into Dinner_Table values('001',10,'大厅中央','未使用');
insert into Dinner_Table values('002',8,'靠走道','未使用');
insert into Dinner_Table values('003',8,'靠窗','未使用');
insert into Dinner_Table values('004',10,'大厅中央','未使用');
insert into Dinner_Table values('005',8,'靠走道','未使用');
insert into Dinner_Table values('006',8,'靠窗','未使用');
insert into Dinner_Table values('007',10,'大厅中央','未使用');
insert into Dinner_Table values('008',8,'水池旁','未使用');
insert into Dinner_Table values('009',4,'秋千椅','未使用');
insert into Dinner_Table values('010',8,'水池旁','未使用');
insert into Dinner_Table values('011',10,'大厅中央','未使用');
insert into Dinner_Table values('012',4,'秋千椅','未使用');
insert into Dinner_Table values('013',8,'水池旁','未使用');
insert into Dinner_Table values('014',8,'大厅中央','未使用');
insert into Dinner_Table values('015',8,'靠窗','未使用');
insert into Dinner_Table values('016',10,'大厅中央','未使用');
insert into Dinner_Table values('017',8,'水池旁','未使用');
insert into Dinner_Table values('018',4,'秋千椅','未使用');
insert into Dinner_Table values('019',4,'秋千椅','未使用');
insert into Dinner_Table values('020',8,'靠窗','未使用');

Create table Client
(
	Client_ID char(6) not null,--从000001开始
	Table_ID char(3),
	Client_Message varchar(10) 
	Primary key(Client_ID),
	Foreign key(Table_ID) references Dinner_Table On delete cascade On update cascade 
);
insert into Client values('000001','001','');
insert into Client values('000002','002','');

Create table Dishes_List
(
	Dishes_ID char(6) not null ,  
	Dishes_Name varchar(20) not null,
	Dishes_Price int not null,
	Dishes_Classification varchar(10) not null,
	Primary key (Dishes_ID )
);
insert into Dishes_List values('100001','白切鸡',8,'特色');
insert into Dishes_List values('100002','潮州卤水鸭',12,'特色');
insert into Dishes_List values('100003','佛跳墙',20,'特色');
insert into Dishes_List values('100004','隆江猪脚',13,'特色');
insert into Dishes_List values('100005','卤肉',8,'特色');

insert into Dishes_List values('200001','凉拌菠菜',8,'凉菜');
insert into Dishes_List values('200002','凉拌海带',5,'凉菜');
insert into Dishes_List values('200003','凉拌黄瓜',8,'凉菜');
insert into Dishes_List values('200004','凉拌金针菇',10,'凉菜');
insert into Dishes_List values('200005','凉拌藕片',9,'凉菜');

insert into Dishes_List values('300001','宫保鸡丁',12,'热菜');
insert into Dishes_List values('300002','回锅肉',10,'热菜');
insert into Dishes_List values('300003','麻婆豆腐',6,'热菜');
insert into Dishes_List values('300004','鱼香茄子',8,'热菜');
insert into Dishes_List values('300005','鱼香肉丝',8,'热菜');

insert into Dishes_List values('400001','鸽子汤',10,'汤类');
insert into Dishes_List values('400002','鸡汤',8,'汤类');
insert into Dishes_List values('400003','鲫鱼汤',9,'汤类');
insert into Dishes_List values('400004','排骨汤',10,'汤类');
insert into Dishes_List values('400005','猪肝汤',6,'汤类');

insert into Dishes_List values('500001','白饭',1,'主食');
insert into Dishes_List values('500002','及第粥',2,'主食');
insert into Dishes_List values('500003','面包',2,'主食');
insert into Dishes_List values('500004','扬州炒饭',3,'主食');
insert into Dishes_List values('500005','意大利拉面',5,'主食');

insert into Dishes_List values('600001','橙汁',3,'酒水');
insert into Dishes_List values('600002','菊花茶',1,'酒水');
insert into Dishes_List values('600003','咖啡',15,'酒水');
insert into Dishes_List values('600004','可口可乐',3,'酒水');
insert into Dishes_List values('600005','珠江啤酒',15,'酒水');

insert into Dishes_List values('700001','冬菇鸡腿饭套餐',12,'套餐');
insert into Dishes_List values('700002','肥牛饭套餐',14,'套餐');
insert into Dishes_List values('700003','麦当劳套餐',10,'套餐');
insert into Dishes_List values('700004','蒜香辣骨饭套餐',10,'套餐');
insert into Dishes_List values('700005','原盅蒸炖鸡套餐',11,'套餐');


Create table Bill 
(
	Bill_ID  char(6) not null ,--从200001开始
	Client_ID char(6) not null,--将下单表和账单表合并后加入此属性
	Dishes_ID char(6) not null, 
	Dishes_Name varchar(20) not null,
	Quantity int  not null,
	Price int,
	Foreign key(Client_ID ) references Client On delete cascade On update cascade,
	Foreign key(Dishes_ID) references Dishes_List On delete cascade On update cascade,
	Primary key(Bill_ID,Dishes_ID)
);




--------------------------------------------------------------------------------------------------------

Create table Department
(
	Department_ID char(6),--从100001开始
	Department_Name varchar(10),
	Primary key(Department_ID)
);
insert into Department values('001','厨师部');
insert into Department values('002','服务部');
insert into Department values('003','采购部');

Create table Employee
(
	Employee_ID char(11),
	Employee_Password varchar(6) not null,
	Employee_Name varchar(20),
	Employee_Sex char(2) check(Employee_Sex='男' or Employee_Sex='女'),
	Department_ID char(6),--将员工表和部门隶属表合并后加入此属性
	Employee_Style char(10), 
	Primary key(Employee_ID),
	Foreign key(Department_ID) references Department On delete cascade On update cascade 
);

insert into Employee values('20121003501','123456','阿二','女','002','服务员');
insert into Employee values('20121003502','123456','阿三','女','002','服务员');
insert into Employee values('20121003503','123456','阿四','男','002','服务员');
insert into Employee values('20121003504','123456','阿五','女','002','服务员');
insert into Employee values('20121003505','123456','阿六','男','002','服务员');

insert into Employee values('20121003601','123456','王五','女','003','采购员');
insert into Employee values('20121003602','123456','王五','女','003','采购员');
insert into Employee values('20121003603','123456','赵四','男','003','采购员');
insert into Employee values('20121003604','123456','皮卡','女','003','采购员');
insert into Employee values('20121003605','123456','皮蛋','男','003','采购员');

insert into Employee values('20121003701','123456','森典','男','001','厨师');
insert into Employee values('20121003702','654321','李四','男','001','厨师');
insert into Employee values('20121003703','123456','丽丽','女','001','厨师部');
insert into Employee values('20121003704','123456','丫丫','女','001','厨师部');
insert into Employee values('20121003705','123456','明智','男','001','厨师部');
insert into Employee values('20121003706','123456','森典','男','001','厨师部');


Create table Purchase
(
	Goods_ID char(6),
	Employee_ID char(11),
	Goods_Name char(20),
	Goods_Quantity int,
	Purchase_Date char(10),
	Foreign key(Employee_ID) references Employee On delete cascade On update cascade,
	Primary key(Goods_ID)
);
insert into Purchase values('300001','20121003601','虾',200,'2014-05-22');--虾斤
insert into Purchase values('300002','20121003602','海鱼',200,'2014-05-22');--海鱼斤
insert into Purchase values('300003','20121003603','牛肉',200,'2014-05-22');--牛肉斤
insert into Purchase values('300004','20121003604','油菜',100,'2014-05-22');--油菜斤
insert into Purchase values('300005','20121003605','土豆',100,'2014-05-22');--土豆斤
insert into Purchase values('300006','20121003605','西红柿',100,'2014-05-22');--西红柿斤
insert into Purchase values('300007','20121003604','花菜',100,'2014-05-22');--花菜斤
insert into Purchase values('300008','20121003603','鸡',50,'2014-05-22');--鸡只
insert into Purchase values('300009','20121003602','鸭',50,'2014-05-22');--鸭只
insert into Purchase values('300010','20121003601','鹅',50,'2014-05-22');--鹅只
insert into Purchase values('300011','20121003601','木瓜',150,'2014-05-22');--木瓜斤
insert into Purchase values('300012','20121003602','莴笋',100,'2014-05-22');--莴笋斤
insert into Purchase values('300013','20121003601','鸡蛋',300,'2014-05-22');--鸡蛋个
insert into Purchase values('300014','20121003601','粗盐',50,'2014-05-22');--盐袋
insert into Purchase values('300015','20121003603','鲁花花生油',20,'2014-05-22');--油桶
insert into Purchase values('300016','20121003603','泰国香米',10,'2014-05-22');--米袋
insert into Purchase values('300017','20121003604','面粉',60,'2014-05-22');--面粉袋
insert into Purchase values('300018','20121003604','太太乐鸡精',10,'2014-05-22');--鸡精罐
insert into Purchase values('300019','20121003604','培根',60,'2014-05-22');--培根罐
insert into Purchase values('300020','20121003601','芝士',60,'2014-05-22');--芝士盒
insert into Purchase values('300021','20121003601','乳鸽',100,'2014-05-22');--乳鸽只
insert into Purchase values('300022','20121003601','排骨',200,'2014-05-22');--排骨斤
insert into Purchase values('300023','20121003601','糖',60,'2014-05-22');--糖斤
insert into Purchase values('300024','20121003601','面',100,'2014-05-22');--面斤
insert into Purchase values('300025','20121003602','粉条',100,'2014-05-22');--粉条斤

Create table Goods
(
	Goods_ID char(6),--从300001开始
	Goods_Name varchar(20),
	Goods_Price int,
	Foreign key(Goods_ID) references Purchase On delete cascade On update cascade,
	Primary key(Goods_ID)
);
insert into Goods values('300001','虾',300);
insert into Goods values('300002','海鱼',450);
insert into Goods values('300003','牛肉',300);
insert into Goods values('300004','油菜',100);
insert into Goods values('300005','土豆',150);
insert into Goods values('300006','西红柿',150);
insert into Goods values('300007','花菜',150);
insert into Goods values('300008','鸡',250);
insert into Goods values('300009','鸭',240);
insert into Goods values('300010','鹅',300);
insert into Goods values('300011','木瓜',200);
insert into Goods values('300012','莴笋',100);
insert into Goods values('300013','鸡蛋',300);
insert into Goods values('300014','粗盐',50);
insert into Goods values('300015','鲁花花生油',400);
insert into Goods values('300016','泰国香米',600);
insert into Goods values('300017','面粉',200);
insert into Goods values('300018','太太乐鸡精',100);
insert into Goods values('300019','培根',200);
insert into Goods values('300020','芝士',300);
insert into Goods values('300021','乳鸽',350);
insert into Goods values('300022','排骨',200);
insert into Goods values('300023','糖',100);
insert into Goods values('300024','面',250);
insert into Goods values('300025','粉条',250);














