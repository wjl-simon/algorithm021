
Deque<String> deque = new LinkedList<String>();

deque.addLast("a");
deque.addLast("b");
deque.addLast("c");
System.out.println(deque);

String str = deque.getLast();
System.out.println(str);
System.out.println(deque);

while(deque.size() > 0){
    System.out.println(deque.getLast());
    deque.removeLast();
}
System.out.println(deque);