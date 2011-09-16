import java.lang.reflect.Method;
import java.util.ArrayList;


public class test {	
	public static class Slot {
		public Slot(Object recv, String fnName, Class<?>[] argts) {
			mReceiver = recv;
			mFnName = fnName;
			mArgts = argts;
		}
		
		public void callback(Object... args) {
			
			try {
				Method fn = mReceiver.getClass().getMethod(mFnName, mArgts);							
				fn.setAccessible(true);
				fn.invoke(mReceiver, args);
			} catch (Exception e) {			
				String msg = "";
				for (Class<?> argt : mArgts)
				{
					msg += argt.getName() + ", ";
				}
				System.out.println("bad args:" + msg);
			}
		}
		
		private Object mReceiver;
		private String mFnName;
		private Class<?>[] mArgts;
	}
	
	public static class Signal {		
		public Signal(Class<?>... argts) {
			mArgts = new Class[argts.length];
			for (int i = 0; i < argts.length; ++i)
			{
				mArgts[i] = argts[i];
			}
		}
		
		public void emit(Object... args) {
			for (Signal signal : mSignals)
			{
				signal.emit(args);
			}
			
			for (Slot slot : mSlots)
			{
				slot.callback(args);
			}
		}
		
		public void connect(Signal signal) {
			mSignals.add(signal);
		}
		
		public void disconnect(Signal signal) {
			mSignals.remove(signal);
		}
		
		public Slot connect(Object recv, String fn) {
			Slot slot = new Slot(recv, fn, mArgts);
			mSlots.add(slot);
			return slot;
		}
		
		public void disconnect(Slot slot) {
			mSlots.remove(slot);
		}
		
		private Class<?>[] mArgts;
		private ArrayList<Slot> mSlots = new ArrayList<Slot>();
		private ArrayList<Signal> mSignals = new ArrayList<Signal>();
	}
		
	public static class TestA{
		public void onEvent0() {
			System.out.println("onEvent0:" + "void");
		}
		
		public void onEvent1(Float num) {
			System.out.println("onEvent1:" + num);
		}
		
		public void onEvent2(Integer num, String str)
		{
			System.out.println("onEvent2:" + num + "," + str);
		}
	}
		
	public static void main(String[] args) {
		System.out.println("hello world!");

		TestA testa = new TestA();
		
		Signal sig0 = new Signal();
		sig0.connect(testa, "onEvent0");
		sig0.emit();
		
		Signal sig1 = new Signal(Float.class);
		sig1.connect(testa, "onEvent1");
		sig1.emit(99.8F);
		
		Signal sig2 = new Signal(Integer.class, String.class);	
		sig2.emit(100, "this is signal/slot!");
		sig2.connect(testa, "onEvent2");
		sig2.emit(100, "this is signal/slot!");
		sig2.emit(1000, "this is signal/slot!");
		
		Signal sig00 = new Signal();
		sig00.connect(sig0);
		sig00.emit();
	}	

}