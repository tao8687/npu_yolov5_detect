#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <stdbool.h>
#if defined(ARM_LINUX) ||  defined(LINUX_X86)
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>
#include <dirent.h>
#else
#include <io.h>
#endif
#include <vector>
#include <string>
#include <map>
#include <queue>

#include "sample_comm.h"
#if defined(ARM_LINUX) ||  defined(LINUX_X86)
#define STRNCASECMP strncasecmp
#else
#define STRNCASECMP strnicmp
#endif
#define _TRUE 1
#define _FALSE 0
using namespace std;
VIM_U32 SAMPLE_COMM_FileGetSize(const VIM_CHAR *filename)
{
    FILE *pFile = NULL;
    VIM_U32 u32Len;

    if (filename == NULL)
    {
        printf("the filename is NULL.\n");
        return 0;
    }

    pFile = fopen(filename, "rb");
    if (pFile == NULL)
    {
        printf("cant open %s\n", filename);
        return 0;
    }

    fseek(pFile, 0L, SEEK_END);
    u32Len = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);
    fclose(pFile);

    return u32Len;
}

VIM_U32 SAMPLE_COMM_FileLoad(const VIM_CHAR *filename, VIM_S32 *pData, VIM_U32 u32Len)
{
    FILE *pFile = NULL;

    if (filename == NULL)
    {
        printf("the filename is NULL.\n");
        return 1;
    }

    pFile = fopen(filename, "rb");
    if (pFile == NULL)
    {
        printf("cant open %s\n", filename);
        return 1;
    }

    if (u32Len != fread(pData, 1, u32Len, pFile))
    {
        printf("read %s error.\n", filename);
        return 1;
    }

    fclose(pFile);

    return VIM_SUCCESS;
}

VIM_U32 SAMPLE_COMM_FileSave(VIM_CHAR *filename, VIM_S32 *pData, VIM_U32 u32Len)
{
    FILE *pFile = NULL;

    if (filename == NULL)
    {
        printf("the filename is NULL.\n");
        return 1;
    }

    pFile = fopen(filename, "wb");
    if (pFile == NULL)
    {
        printf("cant open %s\n", filename);
        return 1;
    }

    fwrite(pData, 1, u32Len, pFile);
    fclose(pFile);

    return VIM_SUCCESS;
}

VIM_S32 SAMPLE_COMM_ToolU8toFloat(VIM_U8 *pIn, VIM_F32 *pOut, VIM_U32 u32FileSize)
{
    VIM_S32 s32Ret = VIM_SUCCESS;
    VIM_U32 i;

    if((pIn == VIM_NULL) || (pOut == VIM_NULL))
    {
        return VIM_FAILURE;
    }

    for(i = 0; i < u32FileSize; i++)
    {
        pOut[i] = (VIM_F32)pIn[i] / 256;
    }

    return s32Ret;
}


VIM_S32 SAMPLE_COMM_SearchFile(VIM_CHAR path[], VIM_CHAR pSuffix[], VIM_CHAR filename[][_FILENAME_LEN])
{
#if defined(WIN_X86)
	VIM_S32 i = 0;
	long hFile = 0;
	struct _finddata_t fileInfo;
	string pathName, exdName;

	if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo)) == -1) {
		return 0;
	}
	do {
		if ((!(fileInfo.attrib&_A_SUBDIR)) &&
			(memcmp(fileInfo.name + strlen(fileInfo.name) - strlen(pSuffix), pSuffix, strlen(pSuffix)) == 0))
		{
			sprintf((char*)&filename[i++], "%s%s", path, fileInfo.name);
		}

	} while (_findnext(hFile, &fileInfo) == 0);
	_findclose(hFile);
	return i;
#elif defined(LINUX_X86)||defined(ARM_LINUX)
	VIM_S32 i=0;
	DIR              *pDir ;   				// 真真DIR真真
	struct dirent    *ent  ;   				// 真真真?dirent真真dirent真真?
	pDir=opendir(path);
	while((ent=readdir(pDir))!=NULL)
	{
		if((ent->d_type != DT_DIR)&&(memcmp(ent->d_name+strlen(ent->d_name)-strlen(pSuffix),pSuffix,strlen(pSuffix))==0))
		{
			sprintf((char*)&filename[i++], "%s/%s", path, ent->d_name);
		}
	}
	closedir(pDir);
	return i;
#endif
}


VIM_S32 stringRemoveDelimiter(VIM_CHAR delimiter, const VIM_CHAR *string)
{
	VIM_S32 string_start = 0;

	while (string[string_start] == delimiter)
	{
		string_start++;
	}

	if (string_start >= (VIM_S32)strlen(string)-1)
	{
		return 0;
	}

	return string_start;
}

VIM_S32 SAMPLE_COMM_CheckCmdLineFlag(const VIM_S32 argc, const VIM_CHAR **argv, const VIM_CHAR *string_ref)
{
	VIM_S32 bFound = _FALSE;
	VIM_S32 i = 1;
	if (argc >= 1)
	{
		for (i = 1; i < argc; i++)
		{
			VIM_S32 string_start = stringRemoveDelimiter('-', argv[i]);
			const VIM_CHAR *string_argv = &argv[i][string_start];

			const VIM_CHAR *equal_pos = strchr(string_argv, '=');
			VIM_S32 argv_length = (VIM_S32)(equal_pos == 0 ? strlen(string_argv) : equal_pos - string_argv);

			VIM_S32 length = (VIM_S32)strlen(string_ref);

			if (length == argv_length && !STRNCASECMP(string_argv, string_ref, length))
			{
				bFound = _TRUE;
				continue;
			}
		}
	}

	return bFound;
}

VIM_S32 SAMPLE_COMM_GetCmdLineArgumentInt(const VIM_S32 argc, const VIM_CHAR **argv, const VIM_CHAR *string_ref)
{
	VIM_S32 bFound = _FALSE;
	VIM_S32 value = -1;
	VIM_S32 i = 1;
	if (argc >= 1)
	{
		for (i = 1; i < argc; i++)
		{
			VIM_S32 string_start = stringRemoveDelimiter('-', argv[i]);
			const VIM_CHAR *string_argv = &argv[i][string_start];
			VIM_S32 length = (VIM_S32)strlen(string_ref);

			if (!STRNCASECMP(string_argv, string_ref, length))
			{
				if (length+1 <= (VIM_S32)strlen(string_argv))
				{
					VIM_S32 auto_inc = (string_argv[length] == '=') ? 1 : 0;
					value = atoi(&string_argv[length + auto_inc]);
				}
				else
				{
					value = 0;
				}

				bFound = _TRUE;
				continue;
			}
		}
	}

	if (bFound)
	{
		return value;
	}
	else
	{
		printf("Not found int\n");
		return 0;
	}
}

VIM_S32 SAMPLE_COMM_GetCmdLineArgumentString(const VIM_S32 argc, const VIM_CHAR **argv,
	const VIM_CHAR *string_ref, VIM_CHAR **string_retval)
{
	VIM_S32 bFound = _FALSE;
	VIM_S32 i = 1;
	if (argc >= 1)
	{
		for (i = 1; i < argc; i++)
		{
			VIM_S32 string_start = stringRemoveDelimiter('-', argv[i]);
			VIM_CHAR *string_argv = (char *)&argv[i][string_start];
			VIM_S32 length = (VIM_S32)strlen(string_ref);

			if (!STRNCASECMP(string_argv, string_ref, length))
			{
				*string_retval = &string_argv[length+1];
				bFound = _TRUE;
				continue;
			}
		}
	}

	if (!bFound)
	{
		*string_retval = NULL;
	}

	return bFound;
}

VIM_U32 SAMPLE_COMM_LoadFile(const char *filename, VIM_S32 *pData, VIM_U32 u32Len)
{
    FILE *pFile = NULL;

    if (filename == NULL)
    {
        printf("the filename is NULL.\n");
        return 1;
    }

    pFile = fopen(filename, "rb");
    if (pFile == NULL)
    {
        printf("cant open %s\n", filename);
        return 1;
    }

    if (u32Len != fread(pData, 1, u32Len, pFile))
    {
        printf("read %s error.\n", filename);
        return 1;
    }

    fclose(pFile);
    return 0;
}

VIM_U32 SAMPLE_COMM_GetFileSize(const char *filename)
{
    FILE *pFile = NULL;
    VIM_U32 u32Len;

    if (filename == NULL)
    {
        printf("the filename is NULL.\n");
        return 0;
    }

    pFile = fopen(filename, "rb");
    if (pFile == NULL)
    {
        printf("cant open %s\n", filename);
        return 0;
    }

    fseek(pFile, 0L, SEEK_END);
    u32Len = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);
    fclose(pFile);
    return u32Len;
}

#if defined(ARM_LINUX) ||  defined(LINUX_X86)

class comm_map {
public:
    std::map<int, void *> map_;
    pthread_mutex_t mutex_;
};

VIM_VOID *SAMPLE_COMM_MapCreate(VIM_VOID)
{
    comm_map *cm = new comm_map();
    pthread_mutex_init(&(cm->mutex_), NULL);
    return (VIM_VOID *)cm;
}

VIM_VOID SAMPLE_COMM_MapDestroy(VIM_VOID *handle)
{
    comm_map *cm =(comm_map *)handle;
    delete cm;
}

VIM_S32 SAMPLE_COMM_MapSet(VIM_VOID *handle, int id, VIM_VOID *element)
{
    comm_map *cm =(comm_map *)handle;

    if (cm->map_.find(id) != cm->map_.end())
        return VIM_FAILURE;
    pthread_mutex_lock(&(cm->mutex_));
    cm->map_[id] = element;
    pthread_mutex_unlock(&(cm->mutex_));
    return VIM_SUCCESS;
}

VIM_S32 SAMPLE_COMM_MapGet(VIM_VOID *handle, int id, VIM_VOID **element)
{
    comm_map *cm =(comm_map *)handle;
    if (cm->map_.find(id) == cm->map_.end())
        return VIM_FAILURE;

    pthread_mutex_lock(&(cm->mutex_));
    *element = cm->map_[id];
    cm->map_.erase(id);
    pthread_mutex_unlock(&(cm->mutex_));
    return VIM_SUCCESS;
}

VIM_U32 SAMPLE_COMM_MapSize(VIM_VOID *handle)
{
    comm_map *cm =(comm_map *)handle;
    VIM_U32 size;
    pthread_mutex_lock(&(cm->mutex_));
    size = cm->map_.size();
    pthread_mutex_unlock(&(cm->mutex_));
    return size;
}

class comm_queue {
public:
    std::queue<void *> queue_;
    pthread_mutex_t mutex_;
    pthread_cond_t condition_;
};

VIM_VOID *SAMPLE_COMM_QueueCreate(VIM_VOID)
{
    comm_queue *cq = new comm_queue();
    pthread_mutex_init(&(cq->mutex_), NULL);
    pthread_cond_init(&(cq->condition_), NULL);
    return (VIM_VOID *)cq;
}

VIM_VOID SAMPLE_COMM_QueueDestroy(VIM_VOID *handle)
{
    comm_queue *cq =(comm_queue *)handle;
    delete cq;
}

VIM_VOID SAMPLE_COMM_QueuePush(VIM_VOID *handle, VIM_VOID *element)
{
    comm_queue *cq =(comm_queue *)handle;

    pthread_mutex_lock(&(cq->mutex_));
    cq->queue_.push(element);
    pthread_cond_signal(&(cq->condition_));
    pthread_mutex_unlock(&(cq->mutex_));
}

VIM_VOID SAMPLE_COMM_QueuePop(VIM_VOID *handle, VIM_VOID **element)
{
    comm_queue *cq =(comm_queue *)handle;

    pthread_mutex_lock(&(cq->mutex_));
    while (cq->queue_.empty())
        pthread_cond_wait(&(cq->condition_), &(cq->mutex_));
    *element = cq->queue_.front();
    cq->queue_.pop();
    pthread_mutex_unlock(&(cq->mutex_));
}

VIM_U32 SAMPLE_COMM_QueueTryPop(VIM_VOID *handle, VIM_VOID **element)
{
    comm_queue *cq =(comm_queue *)handle;

    pthread_mutex_lock(&(cq->mutex_));
    if (cq->queue_.empty()) {
        pthread_mutex_unlock(&(cq->mutex_));
        return VIM_FAILURE;
    }
    *element = cq->queue_.front();
    cq->queue_.pop();
    pthread_mutex_unlock(&(cq->mutex_));
    return VIM_SUCCESS;
}

VIM_U32 SAMPLE_COMM_QueueSize(VIM_VOID *handle)
{
    comm_queue *cq =(comm_queue *)handle;
    VIM_U32 size;

    pthread_mutex_lock(&(cq->mutex_));
    size = cq->queue_.size();
    pthread_mutex_unlock(&(cq->mutex_));
    return size;
}

#ifdef USE_LMDB
#include "caffe.pb.h"

class SAMPLE_COMM_LMDB_HANDLE{
public:
    MDB_env* mdb_env;
    MDB_dbi mdb_dbi;
    MDB_cursor* mdb_cursor;
    MDB_txn* mdb_txn;
    MDB_val mdb_key, mdb_value;
    caffe::Datum datum;
    caffe::AnnotatedDatum anno_datum;
    SAMPLE_COMM_LMDB_HANDLE(): anno_datum(), datum() {};
    ~SAMPLE_COMM_LMDB_HANDLE() {};
};

#define MDB_CHECK(func) \
    mdb_status = func; \
    if (mdb_status != MDB_SUCCESS) { \
        printf("%s failed: %d,   %s\n", #func, mdb_status, mdb_strerror(mdb_status)); \
        return VIM_FAILURE; \
    }

VIM_S32 SAMPLE_COMM_OpenLmdb(const char *filename, void **fd)
{
    int mdb_status;
    SAMPLE_COMM_LMDB_HANDLE *lmdb_fd;
	printf("filename is %s\n",filename);
    //lmdb_fd = (SAMPLE_COMM_LMDB_HANDLE_S *)malloc(sizeof(SAMPLE_COMM_LMDB_HANDLE_S));
    lmdb_fd = new SAMPLE_COMM_LMDB_HANDLE();
    MDB_CHECK(mdb_env_create(&(lmdb_fd->mdb_env)));
    MDB_CHECK(mdb_env_open(lmdb_fd->mdb_env, filename, MDB_NOTLS, 0664));
    MDB_CHECK(mdb_txn_begin(lmdb_fd->mdb_env, NULL, MDB_RDONLY, &(lmdb_fd->mdb_txn)));
    MDB_CHECK(mdb_dbi_open(lmdb_fd->mdb_txn, NULL, 0, &(lmdb_fd->mdb_dbi)));
    MDB_CHECK(mdb_cursor_open(lmdb_fd->mdb_txn, lmdb_fd->mdb_dbi, &(lmdb_fd->mdb_cursor)));
    MDB_CHECK(mdb_cursor_get(lmdb_fd->mdb_cursor, &(lmdb_fd->mdb_key), &(lmdb_fd->mdb_value), MDB_FIRST));

    *fd = (void *)lmdb_fd;
    return VIM_SUCCESS;
}

VIM_VOID SAMPLE_COMM_CloseLmdb(void *fd)
{
    SAMPLE_COMM_LMDB_HANDLE *lmdb_fd = (SAMPLE_COMM_LMDB_HANDLE *)fd;

    mdb_cursor_close(lmdb_fd->mdb_cursor);
    mdb_txn_abort(lmdb_fd->mdb_txn);
    mdb_dbi_close(lmdb_fd->mdb_env, lmdb_fd->mdb_dbi);
    mdb_env_close(lmdb_fd->mdb_env);
}

VIM_S32 SAMPLE_COMM_GetLmdbItemSize(void *fd, VIM_U32 *data_size)
{
    SAMPLE_COMM_LMDB_HANDLE *lmdb_fd = (SAMPLE_COMM_LMDB_HANDLE *)fd;
    lmdb_fd->datum.ParseFromArray(lmdb_fd->mdb_value.mv_data, lmdb_fd->mdb_value.mv_size);
    *data_size = lmdb_fd->datum.data().size();
    printf("data size: %d\n", *data_size);
    printf("data shape: %d %d %d\n", lmdb_fd->datum.channels(), lmdb_fd->datum.height(), lmdb_fd->datum.width());
    return VIM_SUCCESS;
}

VIM_S32 SAMPLE_COMM_GetAnnoItemSize(void *fd, VIM_U32 *data_size, VIM_U32 *label_size)
{
    //caffe::AnnotatedDatum *anno_datum = new caffe::AnnotatedDatum();
    SAMPLE_COMM_LMDB_HANDLE *lmdb_fd = (SAMPLE_COMM_LMDB_HANDLE *)fd;
    //anno_datum->ParseFromArray(lmdb_fd->mdb_value.mv_data, lmdb_fd->mdb_value.mv_size);
    //*data_size = anno_datum->datum().data().size();
    lmdb_fd->anno_datum.ParseFromArray(lmdb_fd->mdb_value.mv_data, lmdb_fd->mdb_value.mv_size);
    *data_size = lmdb_fd->anno_datum.datum().data().size();
    printf("data size: %d\n", *data_size);
    printf("data shape: %d %d %d\n", lmdb_fd->datum.channels(), lmdb_fd->datum.height(), lmdb_fd->datum.width());
    return VIM_SUCCESS;
}

VIM_U32 getAnnoLabel(caffe::AnnotatedDatum &anno_datum, VIM_F32 *pf32TopLabel)
{
    int idx = 0, item_id = 0, lable_num = 0;
    VIM_F32 *top_label = pf32TopLabel;

    for (int g = 0; g < anno_datum.annotation_group_size(); ++g) {
        const caffe::AnnotationGroup& anno_group = anno_datum.annotation_group(g);
        for (int a = 0; a < anno_group.annotation_size(); ++a) {
            const caffe::Annotation& anno = anno_group.annotation(a);
            const caffe::NormalizedBBox& bbox = anno.bbox();
            top_label[idx++] = item_id;
            top_label[idx++] = anno_group.group_label();
            top_label[idx++] = anno.instance_id();
            top_label[idx++] = bbox.xmin();
            top_label[idx++] = bbox.ymin();
            top_label[idx++] = bbox.xmax();
            top_label[idx++] = bbox.ymax();
            top_label[idx++] = bbox.difficult();
            lable_num++;
        }
    }
    return lable_num;
}

VIM_S32 SAMPLE_COMM_ReadLmdb(void *fd, void *data, void *label, VIM_U32 *idx)
{
    int mdb_status;
    static int pic_idx = 0;
    SAMPLE_COMM_LMDB_HANDLE *lmdb_fd = (SAMPLE_COMM_LMDB_HANDLE *)fd;

    lmdb_fd->datum.ParseFromString(std::string(static_cast<const char*>(lmdb_fd->mdb_value.mv_data), lmdb_fd->mdb_value.mv_size)); //TODO: check reture value
    mdb_status = mdb_cursor_get(lmdb_fd->mdb_cursor, &(lmdb_fd->mdb_key), &(lmdb_fd->mdb_value), MDB_NEXT);
    if (mdb_status == MDB_NOTFOUND) {
        mdb_cursor_get(lmdb_fd->mdb_cursor, &(lmdb_fd->mdb_key), &(lmdb_fd->mdb_value), MDB_FIRST);
        return 1;
    } else if (mdb_status != MDB_SUCCESS) {
        printf("mdb_cursor_get failed, %s\n", mdb_strerror(mdb_status));
        return VIM_FAILURE;
    }

    memcpy((char*)data, lmdb_fd->datum.data().c_str(), lmdb_fd->datum.data().size());
    *(VIM_U32*)label = lmdb_fd->datum.label();
    *idx = pic_idx;
    pic_idx++;
    return VIM_SUCCESS;
}

VIM_S32 SAMPLE_COMM_ReadAnnoLmdb(void *fd, void *data, void *label, VIM_U32 *idx)
{
    int mdb_status, label_num;
    static int pic_idx = 0;
    SAMPLE_COMM_LMDB_HANDLE *lmdb_fd = (SAMPLE_COMM_LMDB_HANDLE *)fd;

    lmdb_fd->anno_datum.ParseFromString(std::string(static_cast<const char*>(lmdb_fd->mdb_value.mv_data), lmdb_fd->mdb_value.mv_size)); //TODO: check reture value
    mdb_status = mdb_cursor_get(lmdb_fd->mdb_cursor, &(lmdb_fd->mdb_key), &(lmdb_fd->mdb_value), MDB_NEXT);
    if (mdb_status == MDB_NOTFOUND) {
        mdb_cursor_get(lmdb_fd->mdb_cursor, &(lmdb_fd->mdb_key), &(lmdb_fd->mdb_value), MDB_FIRST);
        printf("Read lmdb dataset reach the end, set curser to first image.\n");
    } else if (mdb_status != MDB_SUCCESS) {
        printf("mdb_cursor_get failed, %s\n", mdb_strerror(mdb_status));
        return VIM_FAILURE;
    }

    memcpy((char*)data, lmdb_fd->anno_datum.datum().data().c_str(), lmdb_fd->anno_datum.datum().data().size());
    label_num = getAnnoLabel(lmdb_fd->anno_datum, (VIM_F32*)(label+16));
    *(int*)label = label_num;
    *idx = pic_idx;
    pic_idx++;
    return VIM_SUCCESS;
}

#else
VIM_S32 SAMPLE_COMM_ReadBin(char astrDataFileList[][_FILENAME_LEN], void *data,  VIM_U32 fsize, VIM_U32 DataIndex)
{
    char *strImageFile;
    char strLabelFile[_FILENAME_LEN];
    VIM_U32 label_num = 0;    
    strImageFile = astrDataFileList[DataIndex];
    //printf(" strImageFile = %s\n ", strImageFile);   
    if (SAMPLE_COMM_FileLoad(strImageFile, (VIM_S32 *)data, fsize)) 
    {
        printf("Read image file %s file fail.\n", strImageFile);
        return VIM_FAILURE;
    }        
    return VIM_SUCCESS;
}
VIM_S32 SAMPLE_COMM_OpenLmdb(const char *filename, void **fd)
{
    printf("Not support lmdb dataset, please rebuild with macro USE_LMDB\n");
    return VIM_FAILURE;
}

VIM_VOID SAMPLE_COMM_CloseLmdb(void *fd) {}
VIM_S32 SAMPLE_COMM_GetLmdbItemSize(void *fd, VIM_U32 *data_size, VIM_U32 *label_size) {return VIM_FAILURE;}
VIM_S32 SAMPLE_COMM_GetAnnoItemSize(void *fd, VIM_U32 *data_size, VIM_U32 *label_size) {return VIM_FAILURE;}
VIM_S32 SAMPLE_COMM_ReadLmdb(void *fd, void *data, void *label, VIM_U32 *idx) {return VIM_FAILURE;}
VIM_S32 SAMPLE_COMM_ReadAnnoLmdb(void *fd, void *data, void *label, VIM_U32 *idx) {return VIM_FAILURE;}
#endif


VIM_S32 SAMPLE_COMM_ReadBinData(char astrDataFileList[][_FILENAME_LEN], void *data, void *label, VIM_U32 *idx, VIM_U32 fsize)
{
    static VIM_U32 u32LabelIdx = 0;
    char *strImageFile;
    char strLabelFile[_FILENAME_LEN];
    VIM_U32 label_num = 0;

    strImageFile = astrDataFileList[u32LabelIdx];
    memcpy(strLabelFile, strImageFile, _FILENAME_LEN);
    char *pTmp = strstr(strLabelFile, ".bin");
    memcpy(pTmp, ".txt", 4);

    if (SAMPLE_COMM_FileLoad(strImageFile, (VIM_S32 *)data, fsize)) {
        printf("Read image file %s file fail.\n", strImageFile);
        return VIM_FAILURE;
    }

    FILE *pFile = fopen(strLabelFile, "rb");
    if (pFile == NULL) {
        printf("Open label file %s failed.\n", strLabelFile);
        return VIM_FAILURE;
    }
    char* pLabelRawBuf = (char *)malloc(1024);
    if (pLabelRawBuf == VIM_NULL) {
        printf("malloc label raw buffer fail.\n");
        fclose(pFile);
        return VIM_FAILURE;
    }
    VIM_F32 *pLabel = (VIM_F32 *)(label + 16);
    VIM_F32 x0, y0, w, h;
    while (1) {
        fgets(pLabelRawBuf, 1024, pFile);
        if (feof(pFile))
            break;
        //sscanf(pLabelRawBuf, "%f %f %f %f %f\n", &(pLabel[1]), &(pLabel[3]), &(pLabel[4]), &(pLabel[5]), &(pLabel[6]));
        sscanf(pLabelRawBuf, "%f %f %f %f %f\n", &(pLabel[1]), &x0, &y0, &w, &h);
        pLabel[0] = 0;
        pLabel[3] = x0-w/2;
        pLabel[4] = y0-h/2;
        pLabel[5] = x0+w/2;
        pLabel[6] = y0+h/2;
        pLabel[7] = 0;
        pLabel += 8;
        label_num ++;
    }
    *(VIM_U32 *)label = label_num;
    free(pLabelRawBuf);
    fclose(pFile);
    *idx = u32LabelIdx;
    u32LabelIdx++;

    return VIM_SUCCESS;
}
#endif
