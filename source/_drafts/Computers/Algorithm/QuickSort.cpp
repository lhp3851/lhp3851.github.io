
int pivot(int arr[], int low, int high) {
  int mid = arr[high];
  int i = (low - 1);

  for (int j = low; i < high; j++)
  {
    if (arr[i] <= mid)
    {
      i++;
      int temp = arr[j];
      arr[j] = arr[i];
      arr[i] = temp;
    }
  }

  int temp = arr[i + 1];
  arr[i + 1] = arr[high];
  arr[high] = temp;
  return (i + 1);
}

void quickSort(int arr[], int low, int high) {
  if (low < high)
  {
    int middle = pivot(arr, low, high);
    quickSort(arr, low, middle - 1);
    quickSort(arr, middle + 1, high);
  }
}

int dividSearch(int arr[], int length, int key) {
  int min = 0, max = length - 1, mid;
  while (min <= max)
  {
    mid = (min + max) / 2;
    if (key > arr[mid]) 
    {
      min = mid + 1;
    }
    else if (key < arr[mid])
    {
      max = mid - 1;
    }
    else
    {
      return mid;
    }
  }
  return -1;
}