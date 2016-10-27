/**
 * Created by bnorbert on 26.10.2016.
 * bnorbertcristian@gmail.com
 */
public class StringNetworkWrapper {

    String message;

    public StringNetworkWrapper(String message){

        int n=0;
        char[] chars=message.toCharArray();
        for(int i=0;i<message.length();i++){
            if(chars[i] == '#'){
                n=i;
                break;
            }
        }

        this.message=message.substring(0,n);

    }

    public String getString(){
        return message;
    }


}
