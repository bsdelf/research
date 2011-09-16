import java.lang.reflect.Method;
import java.util.ArrayList;


public class test {	
	public static class Slot {
		public Slot(Object recv, String fnName) {
			mReceiver = recv;
			mFnName = fnName;
		}
		
		public void callback(Object... args) {
	
			if (mArgts == null)
			{
				mArgts = new Class[args.length];
				for (int i = 0; i < args.length; ++i)
				{
					mArgts[i] = args[i].getClass();
				}
			}
			
			try {
				Method fn = mReceiver.getClass().getMethod(mFnName, mArgts);							
				fn.setAccessible(true);
				fn.invoke(mReceiver, args);
			} catch (Exception e) {			
				e.printStackTrace();
			}
		}
		
		private Object mReceiver;
		private String mFnName;
		private Class<?>[] mArgts;
	}
	
	public static class Signal {
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
			Slot slot = new Slot(recv, fn);
			mSlots.add(slot);
			return slot;
		}
		
		public void disconnect(Slot slot) {
			mSlots.remove(slot);
		}
		
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
		
		Signal sig1 = new Signal();
		sig1.connect(testa, "onEvent1");
		sig1.emit(99.8F);
		
		Signal sig2 = new Signal();	
		sig2.emit(100, "this is signal/slot!");
		sig2.connect(testa, "onEvent2");
		sig2.emit(100, "this is signal/slot!");
		sig2.emit(1000, "this is signal/slot!");
		
		int[] array = new int[0];
		System.out.println(array == null ? "null" : "not null");
		
		Signal sig00 = new Signal();
		sig00.connect(sig0);
		sig00.emit();
	}	

}

/*
public static class Slot<Arg1_t, Arg2_t> {
		public Slot(Object recv, String fnName) {
			mReceiver = recv;
			mFnName = fnName;
		}
		
		public void callback(Arg1_t arg1, Arg2_t arg2) {
			if (mArgts == null)
			{
				mArgts = new Class[2];
				mArgts[0] = arg1.getClass();
				mArgts[1] = arg2.getClass();
			}
			
			try {
				Method fn = mReceiver.getClass().getMethod(mFnName, mArgts);							
				fn.setAccessible(true);
				fn.invoke(mReceiver, arg1, arg2);
			} catch (Exception e) {			
				e.printStackTrace();
			}
		}
		
		private Object mReceiver;
		private String mFnName;
		private Class[] mArgts;
	}
	
	public static class Signal<Arg1_t, Arg2_t> {
		public void emit(Arg1_t arg1, Arg2_t arg2) {
			for (Slot<Arg1_t, Arg2_t> slot : mSlots)
			{
				slot.callback(arg1, arg2);
			}
		}
		
		public Slot<Arg1_t, Arg2_t> connect(Object recv, String fn) {
			Slot<Arg1_t, Arg2_t> slot = new Slot<Arg1_t, Arg2_t>(recv, fn);
			mSlots.add(slot);
			return slot;
		}
		
		public void disconnect(Slot<Arg1_t, Arg2_t> slot) {
			mSlots.remove(slot);
		}
		
		private ArrayList<Slot<Arg1_t, Arg2_t>> mSlots = new ArrayList<Slot<Arg1_t, Arg2_t>>();
	}
*/
