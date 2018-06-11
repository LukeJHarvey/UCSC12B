//-----------------------------------------------------------------------------
// ListIndexOutOfBoundsException.java
//-----------------------------------------------------------------------------

@SuppressWarnings("serial")
public class QueueEmptyException extends IndexOutOfBoundsException{
   public QueueEmptyException(String s){
      super(s);
   }
}