# as-cmd
Playing with ActiveSync protocol

# Used environment variables:
export MY_USER="<user-name>"
export MY_PORT="443"
export MY_PASS="<password>"
export MY_ADDR="outlook.office365.com"

# Example ActiveSync session:
>>> folder-sync
- * * *
- <Add>
- <ServerId>4</ServerId>
- <ParentId>0</ParentId>
- <DisplayName>Inbox</DisplayName>
- <Type>2</Type>
- </Add>
- * * *
>>> set collectionId 4
- [ "collectionId" ]: QVariant(int, 4)
>>> sync
- * * *
- <Sync xmlns="http://synce.org/formats/airsync_wm5/airsync">
- <Collections>
- <Collection>
- <SyncKey>325514121</SyncKey>
- <CollectionId>4</CollectionId>
- <Status>1</Status>
- </Collection>
- </Collections>
- </Sync>
>>> set syncKey 325514121
- [ "syncKey" ]: QVariant(int, 325514121)
>>> sync
- * * *
- <Sync xmlns="http://synce.org/formats/airsync_wm5/airsync">
- <Collections>
- <Collection>
- <SyncKey>293385551</SyncKey>
- <CollectionId>4</CollectionId>
- <Status>1</Status>
 - <Commands>
- <Add>
- * * *
- </Add>
- * * *
- </Collection>
- </Collections>
- </Sync>
