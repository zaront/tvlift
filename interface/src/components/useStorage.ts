import { Dispatch, SetStateAction, useState } from "react";

const storage = localStorage || sessionStorage;

export const useStorage = <T>(key:string, initialValue:T):[T,Dispatch<SetStateAction<T>>] => {
  const [storedValue, setStoredValue] = useState<T>(() => {
    try {
      const item = storage.getItem(key);
      return item ? JSON.parse(item) : initialValue;
    } catch (error) {
      console.log(error);
      return initialValue;
    }
  });

  const setValue : Dispatch<SetStateAction<T>> = (value: T | ((prevState:T)=>T)) => {
    try {
      const valueToStore = value instanceof Function ? value(storedValue) : value as T; //get value
      setStoredValue(valueToStore);
      storage.setItem(key, JSON.stringify(valueToStore));
    } catch (error) {
      console.log(error);
    }
  };

  return [storedValue, setValue];
}