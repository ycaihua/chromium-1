// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_VIEWS_APP_LIST_FOLDER_VIEW_H_
#define UI_APP_LIST_VIEWS_APP_LIST_FOLDER_VIEW_H_

#include "ui/app_list/app_list_item_list_observer.h"
#include "ui/app_list/views/apps_grid_view.h"
#include "ui/app_list/views/apps_grid_view_folder_delegate.h"
#include "ui/app_list/views/folder_header_view.h"
#include "ui/app_list/views/folder_header_view_delegate.h"
#include "ui/compositor/layer_animation_observer.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/view.h"

namespace views {
class ViewModel;
}

namespace app_list {

class AppsContainerView;
class AppsGridView;
class AppListFolderItem;
class AppListItemView;
class AppListMainView;
class AppListModel;
class FolderHeaderView;
class PaginationModel;

class AppListFolderView : public views::View,
                          public FolderHeaderViewDelegate,
                          public AppListModelObserver,
                          public ui::ImplicitAnimationObserver,
                          public AppsGridViewFolderDelegate {
 public:
  AppListFolderView(AppsContainerView* container_view,
                    AppListModel* model,
                    AppListMainView* app_list_main_view);
  virtual ~AppListFolderView();

  void SetAppListFolderItem(AppListFolderItem* folder);

  // Schedules an animation to show or hide the view.
  // If |show| is false, the view should be set to invisible after the
  // animation is done unless |hide_for_reparent| is true.
  void ScheduleShowHideAnimation(bool show, bool hide_for_reparent);

  // Gets icon image bounds of the item at |index|, relative to
  // AppListFolderView.
  gfx::Rect GetItemIconBoundsAt(int index);

  void UpdateFolderNameVisibility(bool visible);

  // Hides the view immediately without animation.
  void HideViewImmediately();

  // Closes the folder page and goes back the top level page.
  void CloseFolderPage();

  // views::View
  virtual gfx::Size GetPreferredSize() OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual bool OnKeyPressed(const ui::KeyEvent& event) OVERRIDE;

  // AppListModelObserver
  virtual void OnAppListItemWillBeDeleted(AppListItem* item) OVERRIDE;

  // ui::ImplicitAnimationObserver
  virtual void OnImplicitAnimationsCompleted() OVERRIDE;

  AppsGridView* items_grid_view() { return items_grid_view_; }

 private:
  void CalculateIdealBounds();

  // Starts setting up drag in root level apps grid view for re-parenting a
  // folder item.
  // |drag_point_in_root_grid| is in the cooridnates of root level AppsGridView.
  void StartSetupDragInRootLevelAppsGridView(
      AppListItemView* original_drag_view,
      const gfx::Point& drag_point_in_root_grid);

  // Overridden from FolderHeaderViewDelegate:
  virtual void NavigateBack(AppListFolderItem* item,
                            const ui::Event& event_flags) OVERRIDE;
  virtual void GiveBackFocusToSearchBox() OVERRIDE;
  virtual void SetItemName(AppListFolderItem* item,
                           const std::string& name) OVERRIDE;

  // Overridden from AppsGridViewFolderDelegate:
  virtual void UpdateFolderViewBackground(bool show_bubble) OVERRIDE;
  virtual void ReparentItem(AppListItemView* original_drag_view,
                            const gfx::Point& drag_point_in_folder_grid)
      OVERRIDE;
  virtual void DispatchDragEventForReparent(
      AppsGridView::Pointer pointer,
      const gfx::Point& drag_point_in_folder_grid) OVERRIDE;
  virtual void DispatchEndDragEventForReparent(
      bool events_forwarded_to_drag_drop_host) OVERRIDE;
  virtual bool IsPointOutsideOfFolderBoundary(const gfx::Point& point) OVERRIDE;
  virtual bool IsOEMFolder() const OVERRIDE;

  AppsContainerView* container_view_;  // Not owned.
  AppListMainView* app_list_main_view_;   // Not Owned.
  FolderHeaderView* folder_header_view_;  // Owned by views hierarchy.
  AppsGridView* items_grid_view_;  // Owned by the views hierarchy.

  scoped_ptr<views::ViewModel> view_model_;

  AppListModel* model_;  // Not owned.
  AppListFolderItem* folder_item_;  // Not owned.

  scoped_ptr<PaginationModel> pagination_model_;

  bool hide_for_reparent_;

  DISALLOW_COPY_AND_ASSIGN(AppListFolderView);
};

}  // namespace app_list

#endif  // UI_APP_LIST_VIEWS_APP_LIST_FOLDER_VIEW_H_
